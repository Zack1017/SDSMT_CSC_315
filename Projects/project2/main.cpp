#include "Graph.h"

int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);


// ----- Test Graph 1 (D requirements) -----
cout << "----- Test Graph 1 -----\n";
Graph g1(7, true); // directed unweighted
g1.addEdge(0,1);
g1.addEdge(0,2);
g1.addEdge(0,3);
g1.addEdge(1,3);
g1.addEdge(1,4);
g1.addEdge(2,5);
g1.addEdge(3,2);
g1.addEdge(3,5);
g1.addEdge(3,6);
g1.addEdge(4,3);
g1.addEdge(4,6);
g1.addEdge(6,5);


// Topological sort (will throw if cyclic). For this graph it should be a DAG per example.

auto topo = g1.topoSort();
cout << "The following is a Topological Sort of the graph: " ;

    for(int  i=0;i<topo.size();++i)
    { 
        if(i >-1) 
        {
            cout << ' '; 
            cout << topo[i]; 
        }
    } 
        cout << "\n";


cout << (g1.hasPathBFS(0,4)?"There is a path from 0 to 4\n":"There is no path from 0 to 4\n");
cout << (g1.hasPathBFS(5,1)?"There is a path from 5 to 1\n":"There is no path from 5 to 1\n");


auto [dist1,par1] = g1.unweightedSSSP(0);
int t=6; 
if(dist1[t]<(int)1e9)
{ 
    cout << "Distance from 0 to 6: "<<dist1[t]<<", with path: "; 
    auto p = Graph::restorePath(0,t,par1); 
    Graph::printPath(p);
} 
else 
{ 
    cout << "6 unreachable from 0\n"; 
}
cout << "------------------------\n\n";


// ----- Test Graph 2 (C: cycle detection + BFS distances from 1 on an undirected graph with cycles) -----
cout << "----- Test Graph 2 -----\n";
Graph g2(8, true); 
g2.addEdge(1,2); 
g2.addEdge(1,4);
g2.addEdge(2,5); 
g2.addEdge(2,4);
g2.addEdge(3,1);
g2.addEdge(3,6);
g2.addEdge(4,5);
g2.addEdge(4,7);
g2.addEdge(4,6);
g2.addEdge(4,3);
g2.addEdge(5,7);
g2.addEdge(7,6);         
auto cyc = g2.findCycleDirected();
cout << (cyc.first?"The graph contains one or more cycles\n":"The graph is acyclic\n");
auto [dist2, par2] = g2.unweightedSSSP(1);
auto report=[&](int target){ cout << target << ": "; if(dist2[target]<(int)1e9){ cout << dist2[target] << ", with path: "; Graph::printPath(Graph::restorePath(1,target,par2)); } else cout << "Unreachable\n"; };
cout << "Distance from 1 to:\n";
report(0); report(2); report(3); report(4); report(5); report(6); report(7);
cout << "------------------------\n\n";


//Test Graph 3
cout << "----- Test Graph 3 -----\n";
Graph g3(7,true);

g3.addEdge(0,1,2);
g3.addEdge(0,3,1);
g3.addEdge(1,3,3);
g3.addEdge(1,4,10);
g3.addEdge(2,0,4);
g3.addEdge(2,5,15);
g3.addEdge(3,4,2);
g3.addEdge(3,6,4);
g3.addEdge(3,5,8);
g3.addEdge(3,2,2); 
g3.addEdge(4,6,6);
g3.addEdge(6,5,1);
  
cout << "Dijkstra's algorithm for shortest path\n";
auto [d3, par3] = g3.dijkstra(0);
cout << "Distance from 0 to:\n";
for(int v=1; v<7; ++v)
{ 
    cout << v << ": "; 
    if(d3[v]<(1LL<<60))
    { 
        cout << d3[v] << ", with path: ";
         Graph::printPath(Graph::restorePath(0,v,par3));
    } 
    else 
    {
        cout << "Unreachable\n"; 
    }
}

const long long INF = (1LL<<60);
auto FW = g3.floydWarshall(INF);

cout << "Floyd-Warshall:\n";
cout << "  ";
for (int j = 0; j < g3.V(); ++j)
{
    cout << setw(3) << j;
} 
cout << "\n";
for (int i = 0; i < g3.V(); ++i) 
{
    cout << i << " ";
    for (int j = 0; j < g3.V(); ++j) 
    {
        if (FW[i][j] >= (INF/2))
        {
            cout << setw(3) << 'x';
        } 
        else
        {
            cout << setw(3) << FW[i][j];
        }
    }
    cout << "\n";
}

cout << "----- Test Graph 4 -----\n";
Graph g4(6, true);

// use addEdge(u, v, /*w=*/0, /*cap=*/C)
g4.addEdge(0,1,0,4);
g4.addEdge(0,2,0,1);
g4.addEdge(1,2,0,0); 
g4.addEdge(1,3,0,2);
g4.addEdge(1,4,0,2);
g4.addEdge(2,4,0,1);
g4.addEdge(3,5,0,2);
g4.addEdge(4,5,0,3);

long long maxflow = g4.maxFlowEdmondsKarp(0,5);
cout << "Ford-Fulkerson algorithm for Maximum Flow\n";
cout << "The maximum flow between 0 and 5 is: " << maxflow << "\n";
g4.writeLastFlowDOT("g4.dot");
cout << "(Wrote g4.dot)\n";
cout << "------------------------\n\n";

Graph g4b(6, true);
g4b = Graph::readDirectedDOT("../data/i_fg.dot");
maxflow = g4b.maxFlowEdmondsKarp(0,5);
cout << "The maximum flow between 0 and 5 is: " << maxflow << "\n";
g4b.writeLastFlowDOT("g4b.dot");
cout << "(Wrote g4b.dot)\n";


Graph g5(7, true);
g5 = Graph::readUndirectedDOT("../data/prim.dot");
cout << "----- Test Graph 5 -----\n";
cout << "Prim's algorithm for Minimum Spanning Tree\n";
try{
auto [costP, edgesP] = g5.primMST(0);
cout << "The cost of the minimum Spanning tree is: " << costP << "\n\n";
cout << "Kruskal's algorithm for Minimum Spanning Tree\n";
auto [costK, edgesK] = g5.kruskalMST();
cout << "The minimum spanning tree is:\n\n";
for(auto &e: edgesK){ auto [u,v,w]=e; cout << "("<<u<<","<<v<<","<<w<<")\n"; }
}catch(const exception& ex){ cerr << "MST error: "<<ex.what()<<"\n"; }
cout << "------------------------\n\n";
g5.writeDOT("g5.dot");


Graph g6 = Graph::readDirectedDOT("../data/g3.dot", /*labelIsCapacity=*/false);

cout << "Dial's algorithm for shortest path\n";
cout << "Vertex\tDistance from Source\n";

int maxW = 10; // or whatever the max edge weight is for this test
auto [distDial, parDial] = g6.dialSSSP(0, maxW);

for (int i = 0; i < g6.V(); ++i) {
    if (distDial[i] >= (1LL<<59)) 
        cout << i << ":\t" << "INF\n";
    else
        cout << i << ":\t" << distDial[i] << "\n";
}
Graph g7 = Graph::readUndirectedDOT("../data/e1.dot");

g7.printEulerResult();

Graph g8 = Graph::readUndirectedDOT("../data/e2.dot");

g8.printEulerResult();


return 0;
}
 