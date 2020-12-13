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
- Notice that the vertices following the source vertex are in asecnding order.
- The above sample input should be interpreted in the form of undirected edges as follows:
```
(1,3), (1,6)
(2,3), (2,5)
(3,4), (3,5)
(4,5)
(5,6)
 ```
- Each row lists edges from a vertex of the graph.

## Output Format
- The total no. of operations and the time taken for execution are printed out on the terminal.
- 2 files, *A.txt* and *C.txt*, are generated that contain an Euler tour, if it exists, and the total no. of operations respectively.
- In *A.txt*, there are 2 lines. First line pertains to existence of an Euler tour in the given graph, denoted 1 or 0. Second line 
contains the Euler tour, if it exists. For example, if *In2.txt* is the given graph:
```
1
1 2 3 4 2 5 4 7 5 6 7 8 3 1 
```

## Run
- Open the terminal, move into your workspace, clone the repository, and move into the project directory.
```
cd <your_worspace>/
git clone https://github.com/urastogi885/find-euler-path.git
cd find-euler-path/
```
- Compile the source to create an executable
```
gcc euler_tour.c -std=c99 -o euler_tour
```
- Run the executable while providing location of the input file
```
./euler_tour <input_file_location>
For instance:
./euler_tour input/in4.txt
```
- Note that the location of the input file will be relative to your current directory
