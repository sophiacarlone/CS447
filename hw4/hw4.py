import sys
import queue
import graphviz
import pydot

class Graph:
    def __init__(self, vertices):
        self.vertices_set = vertices
        self.graph = [[0] * self.vertices_set for _ in range(self.vertices_set)]
        self.parent = [-1] * self.vertices_set
        self.can_reach = set()

    def add_edge(self, start, end, capacity):
        self.graph[start][end] = capacity

    def bfs(self, start, goal):
        visited = [False] * self.vertices_set
        bfs_queue = queue.Queue()
        bfs_queue.put(start)
        visited[start] = True

        while not bfs_queue.empty():
            top = bfs_queue.get()
            for node, capacity in enumerate(self.graph[top]):
                if not visited[node] and capacity > 0:
                    bfs_queue.put(node)
                    visited[node] = True
                    self.parent[node] = top
                    if node == goal:
                        return True

        return False

    # Calculating value of flow
    def calc_flow(self, source, terminal):
        max_flow = 0

        while self.bfs(source, terminal):
            path_flow = sys.maxsize
            start = terminal
            while start != source:
                path_flow = min(path_flow, self.graph[self.parent[start]][start])
                start = self.parent[start]

            max_flow += path_flow

            curr_node = terminal
            while curr_node != source:
                top = self.parent[curr_node]
                self.graph[top][curr_node] -= path_flow
                self.graph[curr_node][top] += path_flow
                curr_node = top

            self.can_reach = set()
            self.dfs_reachable(source)

        return max_flow

    # Performing DFS to find nodes that can be reached from the source
    def dfs_reachable(self, node):
        self.can_reach.add(node)
        for curr_node, capacity in enumerate(self.graph[node]):
            if capacity > 0 and curr_node not in self.can_reach:
                self.dfs_reachable(curr_node)

    # Printing graph to PNG
    def make_graph(self, filename='graph'):
        dot = graphviz.Digraph(comment='Flow')
        for i in range(self.vertices_set):
            for j in range(self.vertices_set):
                if self.graph[i][j] > 0:
                    dot.edge(str(i), str(j), label=str(self.graph[i][j]))

        dot.render(filename, format='png', cleanup=True)
        print(f"Graph saved as '{filename}.png'.")

    # Taking in graph from text file
    def read_graph(self, filename):
        with open(filename, 'r') as file:
            lines = file.readlines()
            print("File opened")

        for line in lines:
            # print(line)
            if "->" in line:
                # print("Valid line - R G")
                halves = line.strip().split('->')
                start = int(halves[0].strip())
                end = int(halves[1].split('[')[0].strip())
                capacity = int(halves[1].split('[')[1].split(']')[0].split("\"")[1].strip())
                # print(start, end, capacity)
                self.add_edge(start, end, capacity)

    
def calc_source_and_terminal(filename):
    source = 0
    terminal = 0
    with open(filename, 'r') as file:
        lines = file.readlines()

    for line in lines:
        # print(line)
        if '->' in line:
            # print("Valid line - C S&T")
            halves = line.strip().split('->')
            start = int(halves[0].strip())
            end = int(halves[1].split('[')[0].strip())
            if (start <= source):
                source = start
            if (end > terminal):
                terminal = end

    return source, terminal

def calc_num_vertices(filename):
    vertices_set = set()

    with open(filename, 'r') as file:
        lines = file.readlines()

    for line in lines:
        # print(line)
        if '->' in line:
            # print("Valid line - C N V")
            halves = line.strip().split('->')
            vertices_set.add(int(halves[0].strip()))
            vertices_set.add(int(halves[1].split('[')[0].strip()))

    print(max(vertices_set) + 1)
    return max(vertices_set) + 1

# def calc_num_vertices(filename):
#     count = 0
#     with open(filename, 'r') as file:
#         lines = file.readlines()

#     for line in lines:
#         if '->' in lines:
#             count += 1
    
#     return count



if __name__ == "__main__":

    # Taking input from text file in graphviz format
    filename = input("Enter the name of the file you would like to open: ")
    
    num_vertices = calc_num_vertices(filename)

    source, terminal = calc_source_and_terminal(filename)

    graph1 = Graph(num_vertices)

    graph1.read_graph(filename)

    flow = graph1.calc_flow(0, 3)
    print(f"Maximum Flow: {flow}")
    
    witness_cut = graph1.can_reach
    print(f"Witness Cut: {witness_cut}")

    graph1.make_graph('graph')
