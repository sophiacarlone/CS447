import graphviz as gz
from graphviz import Digraph
from collections import defaultdict


# ChatGPT code, trying to test it
class Graph:
    def __init__(self):
        self.graph = defaultdict(dict)

    def add_edge(self, u, v, capacity):
        self.graph[u][v] = capacity

    def min_cut(self, source, terminal):
        residual_graph = self.graph.copy()

        def dfs(node, visited):
            visited.add(node)
            for neighbor, capacity in residual_graph[node].items():
                if neighbor not in visited and capacity > 0:
                    dfs(neighbor, visited)

        max_flow = 0
        while True:
            visited = set()
            dfs(source, visited)
            
            # Check if terminal is reachable from source
            if terminal in visited:
                # Find minimum capacity in the augmenting path
                min_capacity = float('inf')
                path = [(source, float('inf'))]
                for u, v in zip(path, path[1:]):
                    min_capacity = min(min_capacity, residual_graph[u[0]][v[0]])
                
                # Update residual graph
                for u, v in zip(path, path[1:]):
                    residual_graph[u[0]][v[0]] -= min_capacity
                    residual_graph[v[0]][u[0]] += min_capacity
                
                max_flow += min_capacity
            else:
                break

        # Now the residual graph contains the minimum cut
        cut = set()
        dfs(source, cut)

        return max_flow, cut

    def visualize(self, filename='graph'):
        dot = Digraph(comment='Flow Network')
        for u, neighbors in self.graph.items():
            dot.node(str(u))
            for v, capacity in neighbors.items():
                dot.edge(str(u), str(v), label=str(capacity))
        dot.render(filename, format='png', cleanup=True)

# Example usage:
graph = Graph()
graph.add_edge('source', 'A', 10)
graph.add_edge('source', 'B', 5)
graph.add_edge('A', 'B', 15)
graph.add_edge('A', 'terminal', 10)
graph.add_edge('B', 'terminal', 10)

source = 'source'
terminal = 'terminal'

graph.visualize('original_graph')

max_flow, min_cut = graph.min_cut(source, terminal)

print(f"Maximum Flow: {max_flow}")
print(f"Minimum Cut: {min_cut}")

graph.visualize('residual_graph')



