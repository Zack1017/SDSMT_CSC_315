#include "Graph.h"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);



    std::cout << "----- Test Graph 1 -----\n";

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

    auto topo = g1.topoSort();
    std::cout << "The following is a Topological Sort of the graph: " ;

    for(int  i=0;i<topo.size();++i)
    { 
        if(i >-1) 
        {
            std::cout << ' '; 
            std::cout << topo[i]; 
        }
    } 
    std::cout << "\n";
    std::cout << (g1.hasPathBFS(0,4)?"There is a path from 0 to 4\n":"There is no path from 0 to 4\n");
    std::cout << (g1.hasPathBFS(5,1)?"There is a path from 5 to 1\n":"There is no path from 5 to 1\n");

    auto [dist1,par1] = g1.unweightedSSSP(0);
    int t=6; 
    if(dist1[t]<(int)1e9)
    { 
        std::cout << "Distance from 0 to 6: "<<dist1[t]<<", with path: "; 
        auto p = Graph::restorePath(0,t,par1); 
        Graph::printPath(p);
    } 

    else 
    { 
        std::cout << "6 unreachable from 0\n"; 
    }

    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph 2 -----\n";

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
    std::cout << (cyc.first?"The graph contains one or more cycles\n":"The graph is acyclic\n");
    auto [dist2, par2] = g2.unweightedSSSP(1);
    auto report=[&](int target)
    { 
        std::cout << target << ": "; 
        if(dist2[target]<(int)1e9)
        { 
            std::cout << dist2[target] << ", with path: "; 
            Graph::printPath(Graph::restorePath(1,target,par2)); 
        } 
        else 
        {
            std::cout << "Unreachable\n";
        } 
    };
    std::cout << "Distance from 1 to:\n";
    report(0); 
    report(2); 
    report(3); 
    report(4); 
    report(5); 
    report(6); 
    report(7);
    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph 3 -----\n";
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
    
    std::cout << "Dijkstra's algorithm for shortest path\n";
    auto [d3, par3] = g3.dijkstra(0);
    std::cout << "Distance from 0 to:\n";
    for(int v=1; v<7; ++v)
    { 
        std::cout << v << ": "; 
        if(d3[v]<(1LL<<60))
        { 
            std::cout << d3[v] << ", with path: ";
            Graph::printPath(Graph::restorePath(0,v,par3));
        } 

        else 
        {
            std::cout << "Unreachable\n"; 
        }
    }
    const long long INF = (1LL<<60);
    auto FW = g3.floydWarshall(INF);
    std::cout << "Floyd-Warshall:\n";
    std::cout << "  ";

    for (int j = 0; j < g3.V(); ++j)
    {
        std::cout << std::setw(3) << j;
    } 
    std::cout << "\n";

    for (int i = 0; i < g3.V(); ++i) 
    {
        std::cout << i << " ";
        for (int j = 0; j < g3.V(); ++j) 
        {
            if (FW[i][j] >= (INF/2))
            {
                std::cout << std::setw(3) << 'x';
            } 
            else
            {
                std::cout << std::setw(3) << FW[i][j];
            }
        }
        std::cout << "\n";
    }
    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph 4 -----\n";
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
    std::cout << "Ford-Fulkerson algorithm for Maximum Flow\n";
    std::cout << "The maximum flow between 0 and 5 is: " << maxflow << "\n";
    g4.writeLastFlowDOT("g4_flow.dot");
    g4.writePNG("g4_flow.dot", "g4_flow.png");
    std::cout << "(Wrote g4_flow.dot and g4_flow.png)\n";
    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph 5 -----\n";
    Graph g5(7, true);
    g5.loadFromDOT("../data/prim.dot", false, true);
    std::cout << "Prim's algorithm for Minimum Spanning Tree\n";
    auto [costP, edgesP] = g5.primMST(0);
    std::cout << "The cost of the minimum Spanning tree is: " << costP << "\n\n";
    std::cout << "Kruskal's algorithm for Minimum Spanning Tree\n";
    auto [costK, edgesK] = g5.kruskalMST();
    std::cout << "The minimum spanning tree is:\n\n";
    for(auto &e: edgesK)
    { 
        auto [u,v,w]=e; 
        std::cout << "("<<u<<","<<v<<","<<w<<")\n"; 
    }
    g5.writeDOT("g5.dot", "", false);
    g5.writePNG("g5.dot", "g5.png");
    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph 6 -----\n";
    Graph g6(7,true);
    g6.loadFromDOT("../data/g3.dot", true, false);
    std::cout << "Dial's algorithm for shortest path\n";
    std::cout << "Vertex\tDistance from Source\n";
    int maxW = 10;
    auto [distDial, parDial] = g6.dialSSSP(0, maxW);
    for (int i = 0; i < g6.V(); ++i) 
    {
        if (distDial[i] >= (1LL<<59)) 
        {
            std::cout << i << ":\t" << "INF\n";
        }

        else
        {
            std::cout << i << ":\t" << distDial[i] << "\n";
        }
    }
    std::cout << "------------------------\n\n";
    
    
    
    std::cout << "----- Test Graph e1 -----\n";
    Graph g7(7,false);
    g7.loadFromDOT("../data/e1.dot", false, true);
    g7.printEulerResult();
    g7.printEulerResult();
    g7.writeEulerTraversalDOT("g7_euler.dot");
    g7.writePNG("g7_euler.dot", "g7_euler.png");
    std::cout << "(Wrote g7_euler.dot and g7_euler.png)\n";
    std::cout << "------------------------\n\n";



    std::cout << "----- Test Graph e2 -----\n";
    Graph g8(6, false);
    g8.loadFromDOT("../data/e2.dot", false, true);
    g8.printEulerResult();
    g8.writeEulerTraversalDOT("g8_euler.dot");
    g8.writePNG("g8_euler.dot", "g8_euler.png");
    std::cout << "(Wrote g8_euler.dot and g8_euler.png)\n";
    std::cout << "------------------------\n\n";

    return 0;
}
 