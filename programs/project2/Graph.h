#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>

class Graph 
{
    public:
        struct Edge
        {
            int to; 
            long long w; 
            long long cap; 
            int rev;
        };
        Graph(int n=0, bool directed=false);

        int V() const; bool isDirected() const;
        void ensureVertex(int v);
        void addEdge(int u,int v,long long w=1, std::optional<long long> cap=std::nullopt);

        bool hasPathDFS(int s,int t) const;
        bool hasPathBFS(int s,int t) const;
        std::pair<bool,std::vector<int>> findCycleDirected() const;
        std::vector<int> topoSort() const;
        std::pair<std::vector<int>,std::vector<int>> unweightedSSSP(int s) const;
        std::pair<std::vector<long long>,std::vector<int>> dijkstra(int s) const;
        std::vector<std::vector<long long>> floydWarshall(long long INF=(1LL<<60)) const;
        long long maxFlowEdmondsKarp(int s,int t);

        std::pair<long long,std::vector<std::tuple<int,int,long long>>> primMST(int start=0) const;
        std::pair<long long,std::vector<std::tuple<int,int,long long>>> kruskalMST() const;

        
        void writeLastFlowDOT(const std::string& filename) const;

        static std::vector<int> restorePath(int s,int t,const std::vector<int>& par);
        static void printPath(const std::vector<int>& path);
        std::pair<std::vector<long long>, std::vector<int>> dialSSSP(int s, int maxW) const;
        std::vector<int> fleuryEulerTrailOrCircuit() const;
        void printEulerResult() const; 
        void loadFromDOT(const std::string& filename, bool directed = true, bool labelIsCapacity = false);
        bool writePNG(const std::string& dotFile, const std::string& pngFile) const;
        void writeDOT(const std::string& filename, const std::string& title = "", bool directed = false) const;
        void writeEulerTraversalDOT(const std::string& dotFile) const;

    private:
        int n_; bool directed_; std::vector<std::vector<Edge>> adj_;
        mutable std::vector<std::vector<Edge>> lastResidual_{}; mutable int lastS_{-1}, lastT_{-1}; mutable long long lastMaxFlow_{0};
        size_t edgesCount() const;
        static Graph readDirectedDOT(const std::string& filename, bool labelIsCapacity=false);
        static Graph readUndirectedDOT(const std::string& filename);
        void writeDOTUndirectedExpanded(const std::string& filename) const;
        void writeDOTDirectedStrict(const std::string& filename, const std::string& title) const;
};

#endif
