# Find-Euler-Path
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](https://github.com/urastogi885/find-euler-path/blob/main/LICENSE)

## Overview
The goal of this project is to find if an Euler tour (not Euler path) exists for given undirected, connected, simple 
graphs, and to print such a tour, if they do indeed have one.

## Input Format
- The graph is stored in a adjacent list format. In each of the input graphs, vertices are numbered from 1 to
_|V|_.
- Each row includes a vertex, followed by zero or more other vertices. For example:
```
1 3 6
2 3 5
3 1 2 4 5
4 3 5
5 2 3 4 6
6 1 5
```
- Notice that the vertices following the source vertex are in arbitrary order.
- The above sample input should be interpreted in the form of undirected edges as follows:
```
(1,3), (1,6)
(2,3), (2,5)
(3,4), (3,5)
(4,5)
(5,6)
 ```
- Each row lists edges from 1 vertex of the graph.
