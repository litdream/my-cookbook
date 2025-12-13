import json
import networkx as nx
import matplotlib.pyplot as plt

# 1. Load the JSON data (as a string, simulating reading a file)
json_data = ''
with open("sample-data-1.json") as fh:
    json_data = fh.read()
data = json.loads(json_data)

# 2. Initialize the NetworkX graph object
if data["directed"]:
    G = nx.DiGraph()  # Use DiGraph for directed
else:
    G = nx.Graph()    # Use Graph for undirected

# 3. Add Nodes
for node in data["nodes"]:
    # We add the node ID and all other properties (if any)
    G.add_node(node["id"], **{k: v for k, v in node.items() if k != "id"})

# 4. Add Edges
for edge in data["edges"]:
    # Add an edge between source and target, including the weight property
    source = edge["source"]
    target = edge["target"]
    # Pass all other properties (like 'weight') as attributes
    G.add_edge(source, target, **{k: v for k, v in edge.items() if k not in ["source", "target"]})

print("NetworkX Graph successfully loaded.")
print(f"Nodes: {list(G.nodes)}")
print(f"Edges (with weights): {G.edges(data=True)}")



###  Visualize with NetworkX Built-in Drawer
###    - NetworkX relies on the Matplotlib for simple drawing

# --- Continue from the previous script ---


# 1. Set layout for nodes (spring layout is common for general graphs)
pos = nx.spring_layout(G, seed=42) # 'seed' ensures the layout is the same every time

# Extract edge labels (weights) for drawing
edge_labels = nx.get_edge_attributes(G, 'weight')

# 1. Draw the graph components using the correct functions:
# A. Draw Nodes
nx.draw_networkx_nodes(
    G, pos,
    node_color='lightblue',
    node_size=1500,
    alpha=0.9
)

# B. Draw Edges
nx.draw_networkx_edges(
    G, pos,
    edge_color='gray',
    width=2
)

# C. Add Node Labels (The node IDs: N1, N2, etc.)
nx.draw_networkx_labels(
    G, pos,
    font_size=12,
    font_color='black',
    font_weight='bold'
)

# D. Add Edge Labels (The weights: 2, 4, 6, etc.)
nx.draw_networkx_edge_labels(
    G, pos,
    edge_labels=edge_labels,
    font_color='red'
)

# Set the title and display the plot
plt.title("JSON Graph Visualization (using NetworkX and Matplotlib)")
plt.axis('off') # Turn off the Matplotlib axis frame
plt.show()
