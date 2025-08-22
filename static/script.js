// const API_URL = "http://127.0.0.1:8000/search";

const API_URL = (location.hostname === "localhost" ? "http://127.0.0.1:8000" : "") + "/search";

const chatbox = document.getElementById("chatbox");
const input = document.getElementById("user-input");

async function sendMessage() {
  const question = input.value.trim();
  if (!question) return;

  const userMsg = document.createElement("div");
  userMsg.className = "message user";
  userMsg.innerHTML = question;
  chatbox.appendChild(userMsg);

  const botMsg = document.createElement("div");
  botMsg.className = "message bot";
  botMsg.innerHTML = "Thinking...";
  chatbox.appendChild(botMsg);

  chatbox.scrollTop = chatbox.scrollHeight;
  input.value = "";

  try {
    const res = await fetch(`${API_URL}?query=${encodeURIComponent(question)}`);
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    const data = await res.json();
    botMsg.innerHTML = "";

    if (data.count > 0 && Array.isArray(data.results) && data.results.length) {
      botMsg.innerHTML = `<strong>Bot:</strong><br>`;
      data.results.forEach(item => {
        const card = document.createElement("div");
        card.className = "card";
        card.style.border = "1px solid #ccc";
        card.style.margin = "5px 0";
        card.style.padding = "8px";
        card.style.borderRadius = "5px";
        card.style.background = "#fafafa";
        card.innerHTML = `
          <div><strong>Code:</strong> ${item.code}</div>
          <div><strong>Title:</strong> ${item.title}</div>
          <div><strong>Description:</strong> ${item.description}</div>
          <div><strong>Trigger:</strong> <code>${item.trigger_condition ?? ""}</code></div>
          <div><strong>Source:</strong> ${item.source ?? ""}</div>
          <div><strong>Solutions:</strong>
            <ul>${(item.solutions || []).map(sol => `<li>${sol}</li>`).join("")}</ul>
          </div>
        `;
        botMsg.appendChild(card);
      });
    } else if (data.message) {
      // LLM fallback
      botMsg.innerHTML = `<strong>Bot:</strong><br><div>${data.message}</div>`;
    } else {
      botMsg.innerHTML = `<strong>Bot:</strong> No answer.`;
    }
  } catch (err) {
    console.error(err);
    botMsg.innerHTML = `<strong>Bot:</strong> Error fetching answer.`;
  }

  chatbox.scrollTop = chatbox.scrollHeight;
}

input.addEventListener("keydown", (e) => {
  if (e.key === "Enter") sendMessage();
});