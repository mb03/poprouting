import networkx as nx,random

g=nx.watts_strogatz_graph(100,10,0.2);
g2=nx.Graph()
for e in g.edges_iter():
	g2.add_edge(e[0],e[1],weight=random.uniform(0,5))
nx.write_weighted_edgelist(g2,"input.edgelist")
