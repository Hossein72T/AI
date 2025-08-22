from fastapi import FastAPI, Request
from fastapi.responses import FileResponse, JSONResponse
from fastapi.staticfiles import StaticFiles
from openai import OpenAI
from dotenv import load_dotenv
import json
import re
import os
from datetime import datetime

# === Load .env ===
load_dotenv()

# === Initialize FastAPI app ===
app = FastAPI()

# === Serve static files like script.js ===
app.mount("/static", StaticFiles(directory="static"), name="static")

# === Load error codes and descriptions from KB ===
KB_PATH = "kb.json"
if not os.path.exists(KB_PATH):
    raise RuntimeError("kb.json not found next to api.py")
with open(KB_PATH, "r", encoding="utf-8") as f:
    KB = json.load(f)

# === Configure OpenAI client (reads OPENAI_API_KEY from .env/env) ===
OPENAI_KEY = os.getenv("OPENAI_API_KEY", "").strip()
if not OPENAI_KEY:
    raise RuntimeError("OPENAI_API_KEY not set. Put it in .env or environment variables.")
client = OpenAI(api_key=OPENAI_KEY)

# === Directory to store live uploaded device data ===
LIVE_DATA_DIR = "live_data"
os.makedirs(LIVE_DATA_DIR, exist_ok=True)


# === Helper: Load telemetry data ===
def load_live_data(device_id: str):
    path = os.path.join(LIVE_DATA_DIR, "{}.json".format(device_id))
    if os.path.exists(path):
        with open(path, "r", encoding="utf-8") as f:
            return json.load(f)
    return None


# === Helper: Search KB entries based on query match score ===
# === Helper: Search KB entries based on query match score (strict) ===
# === Helper: Search KB entries based on token/bigram scoring (strict but robust) ===
def search_kb(query: str, limit: int = 5, min_score: int = 3):
    """
    Token-based scoring:
    - Match unigrams and bigrams against code/title/description/category.
    - Heavier weight for bigram/title/code hits.
    - Filters out weak matches using min_score.
    """
    tokens, bigrams = normalize_query(query)
    if not tokens and not bigrams:
        return []

    scored = []
    for entry in KB:
        code = (entry.get("code") or "").lower()
        title = (entry.get("title") or "").lower()
        desc = (entry.get("description") or "").lower()
        cat  = (entry.get("category") or "").lower()

        # Collect text fields to search
        fields = {
            "code": code,
            "title": title,
            "desc": desc,
            "cat":  cat,
        }

        score = 0

        # Bigram hits are strong (e.g., "air flow")
        for bg in bigrams:
            if bg and (bg in fields["title"] or bg in fields["desc"] or bg in fields["cat"] or bg in fields["code"]):
                score += 4

        # Unigram hits with different weights
        for t in tokens:
            if not t:
                continue
            # exact code piece (e.g., "ui_info", "alm_filter")
            if t in fields["code"]:
                score += 5
            # title is very indicative (UI labels, menu names, alarms)
            if t in fields["title"]:
                score += 3
            # description/category provide weaker evidence
            if t in fields["desc"]:
                score += 2
            if t in fields["cat"]:
                score += 1

        if score >= min_score:
            scored.append((score, entry))

    scored.sort(key=lambda x: x[0], reverse=True)
    return [e for _, e in scored[:limit]]




# === Helper: Build concise, user-facing KB context (no internal codes) ===
def make_kb_context(entries):
    """
    Build a short, human-friendly context from KB hits WITHOUT exposing internal IDs/codes.
    Only include fields a general user can understand.
    """
    lines = []
    for e in entries:
        title = e.get("title", "").strip()
        desc = e.get("description", "").strip()
        causes = e.get("causes", []) or e.get("probable_causes", []) or []
        steps = e.get("steps", []) or e.get("detailed_steps", []) or []
        fixes = e.get("fixes", []) or []
        category = (e.get("category", "") or "").strip()

        block = []
        # Show a friendly heading without code
        if title and category:
            block.append(f"- {title} — {category}")
        elif title:
            block.append(f"- {title}")

        if desc:
            block.append(f"  • Meaning: {desc}")
        if causes:
            block.append("  • Causes: " + ", ".join(causes[:3]))
        if steps:
            block.append("  • Steps: " + "; ".join(steps[:3]))
        if fixes:
            block.append("  • Fixes: " + ", ".join(fixes[:3]))

        lines.append("\n".join(block))

    return "\n".join(lines) if lines else ""



# === Upload telemetry endpoint ===
@app.post("/upload_live_data")
async def upload_live_data(request: Request):
    data = await request.json()
    device_id = data.get("device_id")
    timestamp = data.get("timestamp", datetime.utcnow().isoformat())
    values = data.get("data", {})

    if not device_id or not values:
        return {"status": "error", "message": "device_id and data are required"}

    file_path = os.path.join(LIVE_DATA_DIR, "{}.json".format(device_id))
    with open(file_path, "w", encoding="utf-8") as f:
        json.dump({"device_id": device_id, "timestamp": timestamp, "data": values}, f, indent=2)

    return {"status": "success", "message": "Data saved for device {}".format(device_id)}


# === Firmware search endpoint (ALWAYS hits AI) ===
# === Firmware search endpoint (KB-ONLY mode) ===
@app.get("/search")
def search(query: str, device_id: str = None):
    """
    KB-only behavior:
    - If no sufficiently-strong KB match, return a friendly KB-miss message (no LLM call).
    - If we have KB matches, call the model but constrain it to KB context only.
    - Always keep the answer short (max 3 bullets, ~50 words).
    """
    # 1) Gather KB context with strict threshold
    kb_matches = search_kb(query, limit=5, min_score=3)
    if not kb_matches:
        return {
            "message": (
                "I don't have information about this in our knowledge base. "
                "Please contact company support."
            ),
            "used_kb_codes": [],
            "live_context_present": False,
        }


    kb_context = make_kb_context(kb_matches)

    # (Optional) We can still load live telemetry if you want it displayed.
    # But the model will be instructed to rely strictly on KB for the meaning/steps.
    live_context = ""
    if device_id:
        live_data = load_live_data(device_id)
        if live_data:
            context_lines = []
            for k, v in live_data.get("data", {}).items():
                context_lines.append(f"{k}: {v}")
            live_context = "Live telemetry:\n" + "\n".join(context_lines)

    # 2) Build the prompt for the model (SHORT + KB-ONLY)
    parts = []
    parts.append(f"User query: {query}")
    parts.append("")
    parts.append("KB context:")
    parts.append(kb_context)
    if live_context:
        parts.append("")
        parts.append(live_context)
    parts.append("")
    parts.append("Answer requirements:")
    parts.append("- Use ONLY the KB context above. Do NOT use outside/general knowledge.")
    parts.append("- Do NOT reveal internal IDs, codes, registers, or file names.")
    parts.append("- Speak for general users (non-technical).")
    parts.append("- Output format: maximum 3 short bullet points, ≤ 50 words total.")
    parts.append(
        "- If the KB context is insufficient to answer, reply exactly: 'I don't have information about this in our knowledge base. Please contact company support.'")

    prompt = "\n".join(parts)

    system_prompt = (
        "You are a strict KB-only assistant for an HVAC firmware system. "
        "You must not invent content beyond the provided KB context. "
        "Never reveal internal IDs/codes (e.g., ALM_*, UI_*, MODBUS_*). "
        "Keep answers concise and user-friendly. "
        "If the KB is insufficient, answer with the exact fallback sentence given."
    )

    # 3) Call the model (we have KB matches, so we're allowed)
    # 3) Call the model (we have KB matches, so we're allowed)
    try:
        resp = client.chat.completions.create(
            model="gpt-4o-mini",
            messages=[
                {"role": "system", "content": system_prompt},
                {"role": "user", "content": prompt},
            ],
            temperature=0.1,
            max_tokens=160,  # keep it short
        )
        answer = resp.choices[0].message.content.strip()
        # --- Final safety redaction: strip any bracketed ALL-CAPS codes like [ALM_X], [UI_FOO], [MODBUS_BAR]
        answer = re.sub(r"\[[A-Z0-9_\.:-]{2,}\]", "", answer).strip()

    except Exception as e:
        # Fallback if API call fails
        answer = "Service temporarily unavailable. Please contact company support."

    return {
        "message": answer,
        "used_kb_codes": [e.get("code") for e in kb_matches],
        "live_context_present": bool(live_context),
    }



# === Root endpoint: Serve UI or fallback ===
@app.get("/")
def serve_ui():
    if os.path.exists("index.html"):
        return FileResponse("index.html")
    return JSONResponse({"message": "Chatbot API is online."})


@app.get("/favicon.ico")
async def favicon():
    return FileResponse("static/favicon.ico")




# === Helper: Normalize user query to meaningful tokens ===
def normalize_query(q: str):
    """
    Lowercase, strip punctuation, remove common stopwords (incl. 'ic'),
    and build unigrams + bigrams for better matching (e.g., 'air flow').
    """
    if not q:
        return [], []

    q = q.lower()
    # keep letters, digits, underscore and spaces
    tokens = re.findall(r"[a-z0-9_]+", q)

    # very light stopword list for your domain
    stop = {
        "what", "whats", "is", "are", "the", "a", "an", "of", "in", "on",
        "code", "error", "alarm", "fault", "meaning", "info?", "please",
        "explain", "about", "tell", "me", "define", "definition",
        # ignore 'ic' noise in your chats
        "ic"
    }
    tokens = [t for t in tokens if t not in stop and len(t) >= 2]

    # build bigrams like "air flow"
    bigrams = []
    for i in range(len(tokens) - 1):
        bigrams.append(tokens[i] + " " + tokens[i + 1])

    return tokens, bigrams
