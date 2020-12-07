import numpy as np
from sys import argv


class Graph:
    def __init__(self, adjacency_list):
        self.adj_txt = adjacency_list
        self.vertices, self.edges = [], []
        self.get_vertices()
        self.get_edges()
        self.is_eulerian = self.check_eulerian()

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
        for line in adj_txt.readlines():
            edges = [int(i) for i in line.split()]
            for j in range(1, len(edges)):
                edge = (edges[0]-1, edges[j]-1)
                if not (edge_check_mat[edge[0]][edge[1]] and edge_check_mat[edge[1]][edge[0]]):
                    self.edges.append(edge)
                    edge_check_mat[edge[0]][edge[1]] = 1
                    edge_check_mat[edge[1]][edge[0]] = 1

    def check_eulerian(self):
        adj_txt = open(self.adj_txt, 'r')
        eulerian = True
        for line in adj_txt.readlines():
            vertex_degree = len(line.split()) - 1
            if vertex_degree % 2 != 0:
                eulerian = False
                break
        adj_txt.close()
        return eulerian


script, adjacency_txt = argv


if __name__ == '__main__':
    graph = Graph(adjacency_txt)
    print(graph.vertices)
    print(graph.edges)
    print(graph.is_eulerian)
