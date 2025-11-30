# Graph Algorithms Project — Programming Assignment 2

This project implements a group of classical graph algorithms and outputs results to the console and using Graphviz (DOT → PNG). The implementation supports both directed and undirected graphs and includes DOT parsing, MST algorithms, shortest-path algorithms, max flow, and Euler path generation.

---

## Features Implemented

| Level | Algorithms |
|------|------------|
| **D-Level** | DFS, BFS, Directed Cycle Detection, Topological Sort, Unweighted SSSP |
| **C-Level** | Dijkstra, Floyd-Warshall, Ford-Fulkerson/Edmonds-Karp, Flow graph DOT/PNG |
| **B-Level** | DOT file reader, Prim’s MST, Kruskal’s MST, DOT/PNG output |
| **A-Level** | Dial’s Algorithm, Fleury’s Euler Trail/Circuit w/ traversal-order labels |


*The Level achived is Level A*
---

##  Project Files

| File | Description |
|------|------------|
| `Graph.h` | Header file for Graph class |
| `Graph.cpp` | Implementation of all graph algorithms |
| `main.cpp` | Driver demonstrating all algorithm functionality |
| `CMakeLists.txt` | Build Files and strucutes|
| `*.dot` | Generated DOT files |
| `*.png` | Generated PNG visualizations |
| `Data Folder` | Test Data Files |

---

## Requirements

### C++ & Tools
- C++17 compiler
- CMake 3.10+  
- Graphviz installed and in PATH


## Building and Run
```
mkdir build
cd build
cmake ..
make
./GraphProject
```

## Running Algorithms

All algorithms run when executing the program.
DOT/PNG files are generated in the build directory

## Graph Algorithm Documentation & Usage Guide

This section documents each algorithm implemented in the Graph project, along with small examples showing how to call each method inside `main.cpp`.


### 🔎 Depth-First Search (DFS)

**Function:** `hasPathDFS(int s, int t)`

**Description:**  
Searches for a path between two nodes by exploring as deep as possible before backtracking.

**Use Case:** Path existence & cycle exploration.

**Example:**
```cpp
bool found = g.hasPathDFS(0, 5);
cout << "DFS path exists: " << (found ? "yes" : "no") << endl;
```

**Function:** `findCycleDirected()`

**Description:**  
Detects whether a directed cycle exists using DFS + recursion stack.


**Example:**
```cpp
auto cycle = g.findCycleDirected();
if (cycle.first)
{
    cout << "Cycle Detected: ";
    for (int v : cycle.second) cout << v << " ";
    cout << endl;
}
```

**Function:** `topoSort()`

**Description:**  
Returns topological ordering for a Directed Acyclic Graph (DAG).

**Example:**
```cpp
auto order = g.topoSort();
cout << "Topological Order: ";
for(int v : order) cout << v << " ";
cout << endl;

```

**Function:** `dijkstra(int src)`

**Description:**  
Finds shortest paths from a source in a weighted graph.

**Example:**
```cpp
auto dist = g.dijkstra(0);
cout << "Dijkstra distances:\n";
for (auto &p : dist) cout << p.first << ": " << p.second << endl;
```


**Function:** `floydWarshall()`

**Description:**  
Computes all-pairs shortest paths.

**Example:**
```cpp
auto fw = g.floydWarshall();
cout << "Floyd-Warshall Matrix:\n";
g.printFW(fw);
```


**Function:** `maxFlowEdmondsKarp(int s, int t)`

**Description:**  
Computes maximum flow and updates residual graph.

**Example:**
```cpp
int maxflow = g.maxFlowEdmondsKarp(0, 5);
cout << "Max Flow = " << maxflow << endl;

g.writeLastFlowDOT("flow.dot");
g.writePNG("flow.dot", "flow.png");

```


**Function:** `prim()`

**Example:**
```cpp
auto mst = g.prim();
g.writeDOT("prim.dot", "Prim MST");
g.writePNG("prim.dot", "prim.png");
```


**Function:** `kruskal()`

**Example:**
```cpp
auto mst = g.kruskal();
g.writeDOT("kruskal.dot", "Kruskal MST");
g.writePNG("kruskal.dot", "kruskal.png");
```


**Function:** `dial(int src)`

**Description:**  
Optimized shortest path algorithm for graphs with small integer weights.

**Example:**
```cpp
auto dist = g.dial(0);
for (auto& [v, d] : dist)
    cout << "Node " << v << " dist = " << d << endl
```

**Function:** `fleuryEulerTrailOrCircuit()`

**Example:**
```cpp
g.writeEulerTraversalDOT("euler.dot");
g.writePNG("euler.dot", "euler.png");
```