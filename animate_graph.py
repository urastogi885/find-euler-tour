import numpy as np
from sys import argv


class Graph:
    def __init__(self, adjacency_list):
        self.adj_txt = adjacency_list
        self.count_vertices = self.get_vertices()
        self.edge_check_mat = np.ones((self.count_vertices, self.count_vertices), dtype=np.uint8)
        self.create_edge_check_mat()
        self.is_eulerian = self.check_eulerian()

    def get_vertices(self):
        adj_txt = open(self.adj_txt, 'r')
        count = 0
        for _ in adj_txt.readlines():
            count += 1
        adj_txt.close()
        return count

    def create_edge_check_mat(self):
        adj_txt = open(self.adj_txt, 'r')
        for line in adj_txt.readlines():
            vertices = [int(i) for i in line.split()]
            for j in range(1, len(vertices)):
                edge = (vertices[0]-1, vertices[j]-1)
                if self.edge_check_mat[edge[0]][edge[1]] and self.edge_check_mat[edge[1]][edge[0]]:
                    self.edge_check_mat[edge[0]][edge[1]] = 0
                    self.edge_check_mat[edge[1]][edge[0]] = 0
        adj_txt.close()

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
    if not graph.is_eulerian:
        print('Euler tour does not exist for the given graph!')
        quit()
    v = 0
    euler_tour = [v+1]
    while 0 in graph.edge_check_mat[v]:
        w = np.where(graph.edge_check_mat[v] == 0)[0][-1]
        graph.edge_check_mat[v][w] = 1
        graph.edge_check_mat[w][v] = 1
        v = w
        euler_tour.append(v+1)
    print(euler_tour)
