import os
import re
import json

# Multiple firmware paths
FIRMWARE_PATHS = {
    "CTRL_FAN": r"F:\Avensys-srl\TASK A\Firmware_json\CTRL_FAN_KEIL_1\CTRL_FAN_KEIL_1\Core\Src",
    "KTS": r"F:\Avensys-srl\TASK A\Firmware_json\KTS_SAMG_251\KTS_SAMG_251",
    "RD_ATSAM": r"F:\Avensys-srl\TASK A\Firmware_json\RD_ATSAM4N_V1\RD_ATSAM4N_V1.0_256\RD_ATSAM4N_V1.0\RD_ATSAM4N_V1.0\src"
}

OUTPUT_FILE = "kb.json"

# Regex to detect functions
FUNC_REGEX = re.compile(r"([a-zA-Z_][\w\s\*]+)\s+([a-zA-Z_][\w]*)\s*\([^)]*\)\s*\{")

def analyze_file(file_path, firmware_name):
    results = []
    with open(file_path, "r", errors="ignore") as f:
        lines = f.readlines()

    for i, line in enumerate(lines):
        match = FUNC_REGEX.search(line)
        if match:
            # Try to grab comment line just above function
            description = ""
            if i > 0:
                prev_line = lines[i-1].strip()
                if prev_line.startswith("//") or prev_line.startswith("/*"):
                    description = prev_line.lstrip("/*/ ").strip()

            results.append({
                "firmware": firmware_name,
                "file": os.path.basename(file_path),
                "function": match.group(2),
                "signature": match.group(0).strip("{").strip(),
                "description": description
            })
    return results

def scan_all():
    kb = []
    for fw_name, fw_path in FIRMWARE_PATHS.items():
        for root, _, files in os.walk(fw_path):
            for file in files:
                if file.endswith(".c") or file.endswith(".cpp") or file.endswith(".h"):
                    file_path = os.path.join(root, file)
                    kb.extend(analyze_file(file_path, fw_name))
    return kb

if __name__ == "__main__":
    kb_data = scan_all()
    with open(OUTPUT_FILE, "w") as out:
        json.dump(kb_data, out, indent=2)
    print(f"Extracted {len(kb_data)} functions into {OUTPUT_FILE}")
