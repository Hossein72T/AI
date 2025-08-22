import json

with open("kb.json", "r", encoding="utf-8") as f:
    data = json.load(f)

# Show the first 5 entries to understand structure
for i, item in enumerate(data[:5]):
    print(f"\nEntry {i+1}:")
    for k, v in item.items():
        print(f"  {k}: {str(v)[:100]}")  # print first 100 characters
