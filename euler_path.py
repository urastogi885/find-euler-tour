import numpy as np
from sys import argv


class Graph:
    def __init__(self, adjacency_list):
        self.adj_txt = adjacency_list
        self.is_eulerian = False
        self.vertices, self.edges = [], []
        self.get_vertices()
        self.get_edges()

    def get_vertices(self):
        adj_txt = open(self.adj_txt, 'r')
        count = 0
        for _ in adj_txt.readlines():
            self.vertices.append(count)
            count += 1
        adj_txt.close()

    def get_edges(self):
        edge_check_mat = np.zeros((len(self.vertices), len(self.vertices)))
        adj_txt = open(self.adj_txt, 'r')
        total_degree = 0
        for line in adj_txt.readlines():
            edges = [int(i) for i in line.split()]
            for j in range(1, len(edges)):
                edge = (edges[0]-1, edges[j]-1)
                total_degree += 1
                if not (edge_check_mat[edge[0]][edge[1]] and edge_check_mat[edge[1]][edge[0]]):
                    self.edges.append(edge)
                    edge_check_mat[edge[0]][edge[1]] = 1
                    edge_check_mat[edge[1]][edge[0]] = 1
        self.is_eulerian = (total_degree % 2 == 0)


script, adjacency_txt = argv


if __name__ == '__main__':
    graph = Graph(adjacency_txt)
    print(graph.vertices)
    print(graph.edges)
    print(graph.is_eulerian)
