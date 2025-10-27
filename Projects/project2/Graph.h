#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
using namespace std;

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
        void addEdge(int u,int v,long long w=1, optional<long long> cap=nullopt);

        bool hasPathDFS(int s,int t) const;
        bool hasPathBFS(int s,int t) const;
        pair<bool,vector<int>> findCycleDirected() const;
        vector<int> topoSort() const;
        pair<vector<int>,vector<int>> unweightedSSSP(int s) const;
        pair<vector<long long>,vector<int>> dijkstra(int s) const;
        vector<vector<long long>> floydWarshall(long long INF=(1LL<<60)) const;
        long long maxFlowEdmondsKarp(int s,int t);

        pair<long long,vector<tuple<int,int,long long>>> primMST(int start=0) const;
        pair<long long,vector<tuple<int,int,long long>>> kruskalMST() const;

        void writeDOT(const string& filename,const string& title="",bool includeWeights=true) const;
        static Graph readDOT(const string& filename);
        void writeLastFlowDOT(const string& filename) const;

        static vector<int> restorePath(int s,int t,const vector<int>& par);
        static void printPath(const vector<int>& path);

    private:
        int n_; bool directed_; vector<vector<Edge>> adj_;
        mutable vector<vector<Edge>> lastResidual_{}; mutable int lastS_{-1}, lastT_{-1}; mutable long long lastMaxFlow_{0};
        size_t edgesCount() const;
};

#endif
