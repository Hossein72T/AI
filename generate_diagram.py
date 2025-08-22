import json
from graphviz import Digraph

KB_FILE = "kb.json"
OUTPUT = "firmware_functions"

# Load knowledge base
with open(KB_FILE, "r") as f:
    data = json.load(f)

# Group functions by firmware
functions_by_fw = {}
for item in data:
    fw = item.get("firmware", "Unknown")
    functions_by_fw.setdefault(fw, []).append(item["function"])

# Create a Digraph
dot = Digraph(comment="Firmware Functions Map")
dot.attr(rankdir='LR', size='10,6')

# One cluster per firmware
for fw, funcs in functions_by_fw.items():
    with dot.subgraph(name=f"cluster_{fw}") as c:
        c.attr(label=fw, style="filled", color="lightgrey")
        for func in sorted(set(funcs)):
            node_id = f"{fw}_{func}"
            c.node(node_id, func, shape="box")

# Save the diagram
dot.render(OUTPUT, format="png")
print(f"Diagram saved as {OUTPUT}.png")
