import json
import networkx as nx
import matplotlib.pyplot as plt

# 1. Load the JSON data
with open("sample-data-2.json") as fh:
    json_text = fh.read()
data = json.loads(json_text)

# 2. Initialize the NetworkX graph object
# We'll use DiGraph since your manual conversion represents directed edges
G = nx.DiGraph()

# 3. Add Nodes
G.add_nodes_from(data["nodes"])

# 4. Add Edges (The "Your Way" Logic)
# This is much more efficient: it's a simple nested loop
for source, neighbors in data["graph"].items():
    for target, weight in neighbors.items():
        G.add_edge(source, target, weight=weight)

print(f"Nodes: {list(G.nodes)}")
print(f"Edges: {G.edges(data=True)}")

# --- Visualization ---

# Set layout
pos = nx.spring_layout(G, seed=42)
edge_labels = nx.get_edge_attributes(G, 'weight')

# Draw Nodes
nx.draw_networkx_nodes(G, pos, node_color='lightgreen', node_size=1200)

# Draw Edges (with arrows for directed)
nx.draw_networkx_edges(G, pos, edge_color='gray', width=2, arrowstyle='->', arrowsize=20)

# Labels
nx.draw_networkx_labels(G, pos, font_weight='bold')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color='red')

plt.title("Visualizing Dijkstra-ready Adjacency List")
plt.axis('off')
plt.show()
