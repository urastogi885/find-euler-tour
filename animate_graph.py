import numpy as np
import cv2
from sys import argv


class Graph:
    def __init__(self, adjacency_list: str):
        """
        Initialize a graph using an adjacency list as text input
        :param adjacency_list: location of graph in txt format
        """
        self.img_scaler = 50
        self.adj_txt = adjacency_list
        self.num_vertices = self.count_vertices()
        self.edge_check_mat = np.ones((self.num_vertices, self.num_vertices), dtype=np.uint8)
        self.create_edge_check_mat()

    def count_vertices(self) -> int:
        """
        Count the no .of vertices in the graph
        :return: No. of vertices in the graph
        """
        adj_txt = open(self.adj_txt, 'r')
        count = 0
        for _ in adj_txt.readlines():
            count += 1
        adj_txt.close()
        return count

    def create_edge_check_mat(self) -> None:
        """
        Create an adjacency matrix of the graph
        :return: nothing
        """
        adj_txt = open(self.adj_txt, 'r')
        for line in adj_txt.readlines():
            vertices = [int(i) for i in line.split()]
            for j in range(1, len(vertices)):
                edge = (vertices[0]-1, vertices[j]-1)
                if self.edge_check_mat[edge[0], edge[1]] and self.edge_check_mat[edge[1], edge[0]]:
                    self.edge_check_mat[edge[0], edge[1]] = 0
                    self.edge_check_mat[edge[1], edge[0]] = 0
        adj_txt.close()

    def get_vertex_loc(self, vertex: int, img_size: int) -> tuple:
        text_scalar = 5
        if vertex == 0:
            return (self.img_scaler * (vertex+1), img_size // 2), \
                   (self.img_scaler * (vertex+1) - (2 * text_scalar), img_size // 2)
        elif vertex == self.num_vertices // 2:
            return (self.img_scaler * (vertex+1), img_size // 2), \
                   (self.img_scaler * (vertex+1) + text_scalar, img_size // 2)
        elif 0 < vertex < self.num_vertices // 2:
            return (self.img_scaler * (vertex+1), (img_size // 2) - (2 * self.img_scaler)), \
                   (self.img_scaler * (vertex+1) - text_scalar,
                    (img_size // 2) - (2 * self.img_scaler) - text_scalar)
        else:
            return (self.img_scaler * (self.num_vertices-vertex+1), (img_size // 2) + (2 * self.img_scaler)), \
                   (self.img_scaler * (self.num_vertices-vertex+1) - text_scalar,
                    (img_size // 2) + (2 * self.img_scaler) + (3*text_scalar))

    def animate_euler_tour(self, euler_tour: str) -> None:
        """
        Create an animation of the Euler tour
        :param euler_tour: order of vertices for the Euler tour
        :return: nothing
        """
        x = self.img_scaler * ((self.num_vertices // 2) + 3)
        graph_img = np.zeros((x, x, 3), dtype=np.uint8)
        graph_img.fill(255)
        for vertex in range(self.num_vertices):
            vertex_loc = self.get_vertex_loc(vertex, x)
            cv2.putText(graph_img, str(vertex + 1), vertex_loc[1], cv2.FONT_HERSHEY_SIMPLEX,
                        0.5, (0, 0, 0), 1, cv2.LINE_AA)
            for adj_vertex in range(self.num_vertices):
                if self.edge_check_mat[vertex, adj_vertex] == 0 and self.edge_check_mat[adj_vertex, vertex] == 0:
                    adj_vertex_loc = self.get_vertex_loc(adj_vertex, x)
                    cv2.line(graph_img, vertex_loc[0], adj_vertex_loc[0], (0, 0, 0))
                    self.edge_check_mat[vertex, adj_vertex] = 1
                    self.edge_check_mat[adj_vertex, vertex] = 1

        cv2.imwrite('img.jpg', graph_img)


script, adjacency_txt = argv


if __name__ == '__main__':
    graph = Graph(adjacency_txt)
    graph.animate_euler_tour('C.txt')
