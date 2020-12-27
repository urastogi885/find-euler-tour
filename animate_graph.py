import os
import cv2
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from sys import argv


class Graph:
    def __init__(self, adjacency_list: str):
        """
        Initialize a graph using an adjacency list as text input
        :param adjacency_list: location of graph in txt format
        """
        self.adj_txt = adjacency_list
        self.num_vertices = self.count_vertices()
        self.edges = self.create_edge_check_mat()

    def count_vertices(self) -> int:
        """
        Count the no .of vertices in the graph
        :return: No. of vertices in the graph
        """
        adj_txt = open(self.adj_txt, "r")
        count = 0
        for _ in adj_txt.readlines():
            count += 1
        adj_txt.close()
        return count

    def create_edge_check_mat(self) -> list:
        """
        Create an adjacency matrix of the graph
        :return: list of edges
        """
        edges = []
        # An array to check whether the edge has already been added to the list
        edge_check_mat = np.ones((self.num_vertices, self.num_vertices), dtype=np.uint8)
        adj_txt = open(self.adj_txt, "r")
        for line in adj_txt.readlines():
            vertices = [int(i) for i in line.split()]
            for j in range(1, len(vertices)):
                edge = (vertices[0]-1, vertices[j]-1)
                if edge_check_mat[edge[0], edge[1]] and edge_check_mat[edge[1], edge[0]]:
                    edges.append((edge[0]+1, edge[1]+1))
                    edge_check_mat[edge[0], edge[1]] = 0
                    edge_check_mat[edge[1], edge[0]] = 0
        adj_txt.close()
        return edges

    def animate_euler_tour(self, euler_tour: list) -> None:
        """
        Create an animation of the Euler tour
        :param euler_tour: order of vertices for the Euler tour
        :return: nothing
        """
        # Define the graph with edges
        graph_img = nx.Graph()
        graph_img.add_edges_from(self.edges)
        pos = nx.spring_layout(graph_img)
        # Draw the graph and save it
        nx.draw_networkx(graph_img, pos=pos, with_labels=True)
        plt.savefig(fname="img.jpg")
        img = cv2.imread("img.jpg")
        img_size = img.shape[:2]

        # Define open-cv video recorder to save animation
        video_format = cv2.VideoWriter_fourcc('X', 'V', 'I', 'D')
        video_output = cv2.VideoWriter('euler_tour.avi', video_format, 2.0, (img_size[1], img_size[0]))
        video_output.write(img)

        # Draw the Euler tour
        for i in range(len(euler_tour) - 1):
            nx.draw_networkx_nodes(graph_img, pos, [euler_tour[i]], node_color='r')
            plt.savefig(fname="img.jpg")
            img = cv2.imread("img.jpg")
            video_output.write(img)
            nx.draw_networkx_nodes(graph_img, pos, [euler_tour[i]])
            nx.draw_networkx_edges(graph_img, pos, [(euler_tour[i], euler_tour[i+1])], width=2.0, edge_color='r')
            nx.draw_networkx_nodes(graph_img, pos, [euler_tour[i + 1]], node_color='r')
            plt.savefig(fname="img.jpg")
            img = cv2.imread("img.jpg")
            # Record the last frame for more duration
            if i == len(euler_tour) - 2:
                for _ in range(4):
                    video_output.write(img)
            else:
                video_output.write(img)
        video_output.release()
        cv2.destroyAllWindows()


"""
Define arguments to the script
adjacency_txt: Location of the text file that contains the graph in the form of adjacency list 
"""
script, adjacency_txt = argv


if __name__ == '__main__':
    # Instantiate object of the given graph
    graph = Graph(adjacency_txt)
    # Find euler tour using the c file
    os.system('gcc euler_tour.c -std=c99 -o euler_tour && ./euler_tour ' + adjacency_txt)
    # Extract the output of the c file
    euler_txt = open("A.txt", "r")
    lines = [line for line in euler_txt.readlines()]
    # Animate the Euler tour if it exists in the given graph
    if int(lines[0]):
        tour = [int(v) for v in lines[1].split()]
        graph.animate_euler_tour(tour)
