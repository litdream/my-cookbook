import json
import networkx as nx
import matplotlib.pyplot as plt


import json
import networkx as nx
import matplotlib.pyplot as plt

# The JSON data (you would normally read this from a file)
json_data = """
{
  "graph_name": "6x6 Explicit Maze Graph",
  "directed": false,
  "size": "6x6",
  "start_node": "0_0",
  "end_node": "5_5",
  "nodes": [

    {"id": "0_0", "type": "start"}, {"id": "0_1"}, {"id": "0_2"}, {"id": "0_3"}, {"id": "0_4"}, {"id": "0_5"},

    {"id": "1_0"}, {"id": "1_1"}, {"id": "1_2"}, {"id": "1_3"}, {"id": "1_4"}, {"id": "1_5"},

    {"id": "2_0"}, {"id": "2_1"}, {"id": "2_2"}, {"id": "2_3"}, {"id": "2_4"}, {"id": "2_5"},

    {"id": "3_0"}, {"id": "3_1"}, {"id": "3_2"}, {"id": "3_3"}, {"id": "3_4"}, {"id": "3_5"},

    {"id": "4_0"}, {"id": "4_1"}, {"id": "4_2"}, {"id": "4_3"}, {"id": "4_4"}, {"id": "4_5"},

    {"id": "5_0"}, {"id": "5_1"}, {"id": "5_2"}, {"id": "5_3"}, {"id": "5_4"}, {"id": "5_5", "type": "end"}
  ],
  "edges": [
    {"source": "0_0", "target": "0_1", "weight": 1}, {"source": "0_1", "target": "0_2", "weight": 1},
    {"source": "0_2", "target": "0_3", "weight": 1}, {"source": "0_3", "target": "0_4", "weight": 1},
    {"source": "0_4", "target": "1_4", "weight": 1}, {"source": "0_5", "target": "1_5", "weight": 1},
    {"source": "1_0", "target": "1_1", "weight": 1}, {"source": "1_1", "target": "1_2", "weight": 1},
    {"source": "1_2", "target": "1_3", "weight": 1}, {"source": "1_3", "target": "2_3", "weight": 1},
    {"source": "1_4", "target": "1_5", "weight": 1},
    {"source": "2_0", "target": "3_0", "weight": 1}, {"source": "2_1", "target": "2_2", "weight": 1},
    {"source": "2_2", "target": "2_3", "weight": 1}, {"source": "2_3", "target": "2_4", "weight": 1},
    {"source": "2_4", "target": "2_5", "weight": 1}, {"source": "2_5", "target": "3_5", "weight": 1},
    {"source": "3_0", "target": "3_1", "weight": 1}, {"source": "3_1", "target": "4_1", "weight": 1},
    {"source": "3_2", "target": "4_2", "weight": 1}, {"source": "3_3", "target": "4_3", "weight": 1},
    {"source": "3_4", "target": "4_4", "weight": 1},
    {"source": "4_0", "target": "4_1", "weight": 1}, {"source": "4_0", "target": "5_0", "weight": 1},
    {"source": "4_1", "target": "4_2", "weight": 1}, {"source": "4_3", "target": "4_4", "weight": 1},
    {"source": "4_3", "target": "5_3", "weight": 1}, {"source": "4_4", "target": "4_5", "weight": 1},
    {"source": "4_5", "target": "5_5", "weight": 1},
    {"source": "5_0", "target": "5_1", "weight": 1}, {"source": "5_1", "target": "5_2", "weight": 1},
    {"source": "5_2", "target": "5_3", "weight": 1}, {"source": "5_3", "target": "5_4", "weight": 1},
    {"source": "5_4", "target": "5_5", "weight": 1},
    {"source": "0_0", "target": "1_0", "weight": 1},
    {"source": "1_0", "target": "2_0", "weight": 1},
    {"source": "2_1", "target": "3_1", "weight": 1}, {"source": "2_2", "target": "3_2", "weight": 1},
    {"source": "2_4", "target": "3_4", "weight": 1},
    {"source": "3_3", "target": "4_3", "weight": 1},
    {"source": "4_1", "target": "5_1", "weight": 1}, {"source": "4_2", "target": "5_2", "weight": 1}
  ]
}
"""
data = json.loads(json_data)
G = nx.Graph()

# Build the graph (same as before)
for node in data["nodes"]:
    G.add_node(node["id"], **{k: v for k, v in node.items() if k != "id"})
for edge in data["edges"]:
    G.add_edge(edge["source"], edge["target"], **{k: v for k, v in edge.items() if k not in ["source", "target"]})

print("NetworkX Graph successfully loaded.")
print(f"Nodes: {len(G.nodes)}. Edges: {len(G.edges)}")

# --- CRITICAL: MANUAL POSITIONING FOR GRID LAYOUT ---
pos = {}
for node_id in G.nodes():
    r, c = map(int, node_id.split('_'))
    # (c, -r) maps (column, -row) so that:
    # 1. Columns become the X-axis
    # 2. Row 0 is at the top (highest Y-value)
    pos[node_id] = (c, -r) 

# --- Visualization ---

# Identify special nodes for different colors
start_node = data["start_node"]
end_node = data["end_node"]
node_colors = ['green' if n == start_node else 'red' if n == end_node else 'lightblue' for n in G.nodes()]

plt.figure(figsize=(8, 8)) # Make the plot square

# 1. Draw Nodes
nx.draw_networkx_nodes(
    G, pos,
    node_color=node_colors,
    node_size=500, # Smaller nodes for a grid
    alpha=0.9
)

# 2. Draw Edges (the paths)
nx.draw_networkx_edges(
    G, pos,
    edge_color='black',
    width=3
)

# 3. Add Node Labels (The R_C IDs)
# We draw node labels only for start/end to keep the maze clean
label_pos = {n: (x, y + 0.1) for n, (x, y) in pos.items()} # Slightly offset label
nx.draw_networkx_labels(
    G, pos, 
    labels={start_node: 'Start', end_node: 'End'}, 
    font_size=10, 
    font_weight='bold'
)

plt.title("6x6 Maze Graph Visualization")
plt.axis('equal') # Important for grid aspect ratio
plt.axis('off')
plt.show()



