#include "Graph.h"
using namespace std;

// Local Disjoint-Set (Union-Find) for Kruskal
namespace 
{
    struct DisjointSet 
    {
        vector<int> p, r;
        explicit DisjointSet(int n=0)
        { 
            reset(n); 
        }
        void reset(int n)
        { 
            p.resize(n);
             r.assign(n,0);
            iota(p.begin(), p.end(), 0);
        }
        int find(int x)
        { 
            return p[x]==x? x : p[x]=find(p[x]); 
        }
        bool unite(int a,int b)
        { 
            a=find(a);
            b=find(b); 
            if(a==b)
            {
                return false;
            }  
            if(r[a]<r[b])
            {
                swap(a,b);
            }  
            p[b]=a; 
            if(r[a]==r[b])
            {
                r[a]++;
            }  
            return true; 
        }
    };
}



// ===== Constructors =====
Graph::Graph(int n, bool directed): n_(n), directed_(directed) { adj_.assign(n_, {}); }
int Graph::V() const 
{ 
    return n_; 
}



bool Graph::isDirected() const 
{ 
    return directed_; 
}



void Graph::ensureVertex(int v)
{ 
    if(v>=n_)
    { 
        adj_.resize(v+1);
        n_ = v+1; 
    }
 }



void Graph::addEdge(int u, int v, long long w, optional<long long> cap)
{
    ensureVertex(max(u,v));
    if(cap.has_value())
    {
        // Flow edge maintain reverse indices for residuals
        Edge a{v, w, *cap, (int)adj_[v].size()};
        Edge b{u, 0, 0, (int)adj_[u].size()};
        adj_[u].push_back(a);
        adj_[v].push_back(b);
    } 
    else 
    {
        adj_[u].push_back(Edge{v, w, -1, -1});
        if(!directed_)
        {
            adj_[v].push_back(Edge{u, w, -1, -1});
        } 
    }
}



// ===== D: DFS/BFS path existence =====
bool Graph::hasPathDFS(int s, int t) const
{
    if(s<0||t<0||s>=n_||t>=n_)
    {
        return false;
    } 
    vector<char> vis(n_);
    stack<int> st; 
    st.push(s); 
    vis[s]=1;

    while(!st.empty())
    {
        int u=st.top(); 
        st.pop();
        if(u==t)
        {
            return true;
        } 
        for(const auto &e: adj_[u])
        {
            if(e.cap<0)
            { 
                if(!vis[e.to])
                { 
                    vis[e.to]=1;
                    st.push(e.to);
                } 
            }
        } 
    }
    return false;
}



bool Graph::hasPathBFS(int s, int t) const
{
    if(s<0||t<0||s>=n_||t>=n_)
    {
        return false;
    } 
    vector<char> vis(n_);
    queue<int> q;
    q.push(s); 
    vis[s]=1;

    while(!q.empty())
    {
        int u=q.front(); 
        q.pop();
        if(u==t)
        {
            return true;
        } 
        for(const auto &e: adj_[u])
        {
            if(e.cap<0)
            { 
                if(!vis[e.to])
                { 
                    vis[e.to]=1;
                    q.push(e.to);
                } 
            }
        } 
    }
    return false;
}



// ===== D: Cycle finding on directed graphs =====
pair<bool, vector<int>> Graph::findCycleDirected() const
{
    vector<int> color(n_,0), par(n_,-1), cyc; 
    int start=-1, end=-1;
    function<bool(int)> dfs = [&](int u)
    {
        color[u]=1;
        for(const auto &e: adj_[u])
        {
            if(e.cap<0)
            {
                int v=e.to;
                if(color[v]==0)
                { 
                    par[v]=u; 
                    if(dfs(v))
                    {
                        return true;
                    }  
                }
                else if(color[v]==1)
                { 
                    start=v; 
                    end=u; 
                    return true; 
                }
            }
        }
         
        color[u]=2;
        return false;
    };
    for(int i=0;i<n_;++i)
    { 
        if(color[i]==0 && dfs(i))
        {
            break;
        }  
    }
    if(start==-1)
    {
        return {false,{}};
    } 
    cyc.push_back(start); 
    for(int v=end; v!=start; v=par[v])
    {
        cyc.push_back(v);
    }  
    reverse(cyc.begin(), cyc.end());
    return {true, cyc};
}



// ===== D: Topological sort (Kahn) =====
vector<int> Graph::topoSort() const
{
    vector<int> indeg(n_,0);
    for(int u=0;u<n_;++u)
    {
        for(const auto &e: adj_[u])
        {
            if(e.cap<0) 
            {
                indeg[e.to]++;
            }
        } 
    } 
    queue<int> q; 
    for(int i=0;i<n_;++i)
    {
        if(indeg[i]==0) 
        {
            q.push(i);
        }
    } 
    vector<int> order; 
    order.reserve(n_);
    while(!q.empty())
    {
        int u=q.front(); 
        q.pop(); 
        order.push_back(u);
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0)
            { 
                if(--indeg[e.to]==0) 
                {
                    q.push(e.to);
                } 
            }
        }
    }
    if((int)order.size()!=n_)
    {
        throw runtime_error("Graph has cycles; topological sort undefined");
    } 
    return order;
}



// ===== D: Unweighted SSSP (BFS) =====
pair<vector<int>, vector<int>> Graph::unweightedSSSP(int s) const
{
    const int INF=1e9; 
    vector<int> dist(n_,INF), par(n_,-1); 
    if(s<0||s>=n_)
    {
        return {dist,par};
    } 
    queue<int> q; 
    dist[s]=0; 
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(const auto &e: adj_[u])
        {
            if(e.cap<0)
            {
                if(dist[e.to]>dist[u]+1)
                { 
                    dist[e.to]=dist[u]+1;
                    par[e.to]=u; 
                    q.push(e.to); 
                }
            }    
        }
    }
    return {dist, par};
}



// ===== C: Dijkstra (non-negative weights) =====
pair<vector<long long>, vector<int>> Graph::dijkstra(int s) const
{
    const long long INF=(1LL<<60); 
    vector<long long> d(n_,INF); 
    vector<int> par(n_,-1);
    if(s<0||s>=n_)
    {
        return {d,par};
    } 
    using P=pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    d[s]=0; 
    pq.emplace(0,s);

    while(!pq.empty())
    {
        auto [du,u] = pq.top(); 
        pq.pop(); 
        if(du!=d[u])
        {
            continue;
        } 
        for(const auto &e: adj_[u])
        {
            if(e.cap<0)
            {
                if(e.w<0)
                {
                    continue;
                } 
                long long nd=du+e.w;
                if(nd<d[e.to])
                { 
                    d[e.to]=nd; 
                    par[e.to]=u; 
                    pq.emplace(nd, e.to); 
                }
            }
        } 
        
    }
    return {d, par};
}



// ===== C: Floyd–Warshall =====
vector<vector<long long>> Graph::floydWarshall(long long INF) const
{
    vector<vector<long long>> D(n_, vector<long long>(n_, INF));
    for(int i=0;i<n_;++i) 
    {
        D[i][i]=0;
    }
    for(int u=0;u<n_;++u)
    {   
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0)
            {
                D[u][e.to]=min(D[u][e.to], e.w>=0?e.w:1LL);
            }
        } 
    }  
    for(int k=0;k<n_;++k)
    {
        for(int i=0;i<n_;++i)
        {
            if(D[i][k]<INF)
            {
                for(int j=0;j<n_;++j) 
                { 
                    if(D[k][j]<INF)
                    {
                        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                    }
                }
            }
            
        } 
    }
        
    return D;
}

// ===== C: Ford–Fulkerson (Edmonds–Karp) =====
long long Graph::maxFlowEdmondsKarp(int s, int t)
{
    vector<vector<Edge>> res(n_);
    auto addRes=[&](int u,int v,long long cap)
    {
        Edge a{v,0,cap,(int)res[v].size()};
        Edge b{u,0,0,(int)res[u].size()};
        res[u].push_back(a); 
        res[v].push_back(b);
    };
    for(int u=0;u<n_;++u)
    {
        for(const auto &e: adj_[u])
        {
            if(e.cap>=0) 
            {
                addRes(u,e.to,e.cap);
            }
        } 
    } 

    long long flow=0;
    while(true)
    {
        vector<int> parV(n_,-1), parE(n_,-1);
        queue<int> q; 
        q.push(s);
        parV[s]=s;

        while(!q.empty() && parV[t]==-1)
        {
            int u=q.front(); 
            q.pop();
            for(int i=0;i<(int)res[u].size();++i)
            {
                auto &e=res[u][i];
                if(parV[e.to]==-1 && e.cap>0)
                {
                    parV[e.to]=u; 
                    parE[e.to]=i; 
                    q.push(e.to);
                    if(e.to==t)
                    {
                        break;
                    } 
                }
            }
        }
        if(parV[t]==-1)
        {
            break; // no augmenting path
        } 
        long long aug=LLONG_MAX;
        for(int v=t; v!=s; v=parV[v])
        { 
            auto &e=res[parV[v]][parE[v]]; 
            aug=min(aug, e.cap); 
        }
        for(int v=t; v!=s; v=parV[v])
        { 
            auto &e=res[parV[v]][parE[v]]; 
            auto &rev=res[e.to][e.rev]; 
            e.cap-=aug; rev.cap+=aug; 
        }
        flow+=aug;
    }
    lastResidual_ = move(res); 
    lastS_=s; lastT_=t; 
    lastMaxFlow_=flow;
    return flow;
}

// ===== B: Prim's MST (undirected) =====
pair<long long, vector<tuple<int,int,long long>>> Graph::primMST(int start) const
{
    if(directed_)
    {
        throw runtime_error("Prim requires an undirected graph");
    } 
    if(n_==0) 
    {
        return {0,{}};
    }
    vector<char> vis(n_,0); 
    using T=tuple<long long,int,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    auto push=[&](int u)
    {
        vis[u]=1;
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0)
            { 
                if(!vis[e.to]) 
                {
                    pq.emplace(e.w>=0?e.w:1LL, u, e.to); 
                }
            }
        }
    };
    push(start);
    long long cost=0; 
    vector<tuple<int,int,long long>> edges; 
    edges.reserve(n_?n_-1:0);
    while(!pq.empty() && (int)edges.size()<max(0,n_-1))
    {
        auto [w,u,v]=pq.top(); 
        pq.pop();
        if(vis[v]) 
        {
            continue;
        }
        cost+=w; 
        edges.emplace_back(u,v,w); 
        push(v);
    }
    if((int)edges.size()!=max(0,n_-1)) 
    {
        throw runtime_error("Graph is disconnected; MST not complete");
    }
    return {cost, edges};
}



// ===== B: Kruskal's MST =====
pair<long long, vector<tuple<int,int,long long>>> Graph::kruskalMST() const
{
    if(directed_) 
    {
        throw runtime_error("Kruskal requires an undirected graph");
    }
    struct E{int u,v; long long w;}; 
    vector<E> es; 
    es.reserve(2*edgesCount());

    for(int u=0;u<n_;++u) 
    {
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0)
            {
                if(u<e.to) 
                {
                    es.push_back({u,e.to, e.w>=0?e.w:1LL});
                }
            }
        }
    }
    sort(es.begin(), es.end(), [](const E&a, const E&b)
    { 
        return a.w<b.w; 
    });
    DisjointSet ds(n_); 
    long long cost=0; 
    vector<tuple<int,int,long long>> ans; 
    ans.reserve(n_?n_-1:0);
    for(auto &e: es)
    { 
        if(ds.unite(e.u,e.v))
        { 
            cost+=e.w; 
            ans.emplace_back(e.u,e.v,e.w);
        } 
    }
    if((int)ans.size()!=max(0,n_-1)) 
    {
        throw runtime_error("Graph is disconnected; forest built");
    }
    return {cost, ans};
}



// ===== DOT write/read =====
void Graph::writeDOT(const string& filename, const string& title, bool includeWeights) const
{
    ofstream out(filename); 
    if(!out) 
    {
        throw runtime_error("Cannot open "+filename);
    }
    if(directed_) 
    {
        out << "strict digraph \"" << (title.empty()?"G":title) << "\" {\n\n";
    }
    else 
    {
        out << "graph {\n\n";
    }
    out << "    rankdir=LR;\n";
    for(int u=0;u<n_;++u)
    {
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0)
            {
                if(!directed_ && u>e.to) 
                {
                    continue; // avoid dup in undirected
                }
                out << "    " << u << (directed_?" -> ":" -- ") << e.to;
                if(includeWeights)
                {
                    out << " [label=\"" << (e.w>=0?e.w:1) << "\"]";
                }  
                out << "\n\n";
            }
        }
    }
    out << "}\n";
}

// --- helper (only include if you don't already have it) ---
static long long extract_label_weight(const std::string& attrs) {
    // Finds: label=NUMBER (quoted or not), returns 1 if not found
    std::regex labRe(R"(label\s*=\s*\"?(-?\d+)\"?)");
    std::smatch m;
    if (std::regex_search(attrs, m, labRe)) return std::stoll(m[1]);
    return 1;
}

Graph Graph::readDirectedDOT(const std::string& filename, bool labelIsCapacity)
{
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Cannot open " + filename);

    std::string content((std::istreambuf_iterator<char>(in)),
                         std::istreambuf_iterator<char>());

    // Force directed graph
    Graph g(0, /*directed=*/true);

    // Match:  u -> v [ ...attrs... ]
    // Capture the full attr block so we can extract label even with extra attrs.
    // [^\]]* is used so it can span spaces/newlines until the closing ']'.
    std::regex edgeRe(R"(([0-9]+)\s*->\s*([0-9]+)\s*(?:\[([^\]]*)\])?)");

    // Optional: avoid exact duplicate edges (same u,v,label)
    std::set<std::tuple<int,int,long long>> seen;

    for (std::sregex_iterator it(content.begin(), content.end(), edgeRe), ed; it != ed; ++it) {
        int u = std::stoi((*it)[1]);
        int v = std::stoi((*it)[2]);

        long long val = 1; // default if no label present
        if ((*it)[3].matched) {
            const std::string attrs = (*it)[3].str();
            val = extract_label_weight(attrs);
        }

        // Deduplicate identical lines (optional but handy for DOT exports with repeats)
        auto key = std::make_tuple(u, v, val);
        if (!seen.insert(key).second) continue;

        if (labelIsCapacity) {
            // For flow graphs: label is CAPACITY; weight is unused (set 0)
            g.addEdge(u, v, /*w=*/0, /*cap=*/val);
        } else {
            // For weighted directed graphs: label is WEIGHT
            g.addEdge(u, v, /*w=*/val);
        }
    }

    return g;
}


Graph Graph::readUndirectedDOT(const string& filename)
{
    ifstream in(filename);
    if(!in)
        throw runtime_error("Cannot open " + filename);

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    Graph g(0, false); // undirected = false

    // regex to match: u -- v [label="w"]
    regex edgeRe(R"(([0-9]+)\s*--\s*([0-9]+)\s*(?:\[\s*label\s*=\s*\"?(-?[0-9]+)\"?\s*\])?)");
    auto it = sregex_iterator(content.begin(), content.end(), edgeRe);
    auto end = sregex_iterator();

    set<pair<int,int>> seen; // to avoid duplicates like 1--0 after adding 0--1

    for(; it != end; ++it)
    {
        int u = stoi((*it)[1]);
        int v = stoi((*it)[2]);
        long long w = (*it)[3].matched ? stoll((*it)[3]) : 1;

        // enforce ordering (smaller first) to avoid reverse duplicates
        pair<int,int> key = (u < v) ? make_pair(u,v) : make_pair(v,u);

        if(seen.count(key)) 
            continue;

        seen.insert(key);
        g.addEdge(u, v, w);
    }

    return g;
}







// ===== Flow result DOT =====
void Graph::writeLastFlowDOT(const std::string& filename) const
{
    if (lastResidual_.empty())
        throw std::runtime_error("Run maxFlowEdmondsKarp first");

    std::ofstream out(filename);
    if (!out)
        throw std::runtime_error("Cannot open " + filename);

    out << "strict digraph \"Flow Graph\" {\n\n    rankdir=LR;\n";

    for (int u = 0; u < n_; ++u)
    {
        for (const auto& orig : adj_[u])
        {
            if (orig.cap < 0) continue;  // only flow graph edges (those given with cap)

            const int v = orig.to;
            const long long cap = orig.cap;

            // find the residual entry for u->v to get what flow was sent
            long long flow = 0;
            for (const auto& re : lastResidual_[u])
                if (re.to == v)
                {
                    flow = lastResidual_[v][re.rev].cap;
                    break;
                }

            // --- show zero-capacity edges WITHOUT labels ---
            if (cap == 0)
            {
                out << "    " << u << " -> " << v << "\n";
                continue;
            }

            // Normal positive-capacity edge: show flow/cap
            out << "    " << u << " -> " << v
                << " [label=\"" << flow << "/" << cap << "\"]\n";
        }
    }

    out << "}\n";
}





// ===== Helpers =====
vector<int> Graph::restorePath(int s, int t, const vector<int>& par)
{
    vector<int> path;

    if (t < 0 || t >= (int)par.size())
        return path;

    if (s == t) {                // handle s==t explicitly
        path.push_back(s);
        return path;
    }

    if (par[t] == -1)            // no path
        return path;

    // Build backwards, then reverse ONCE (FIX: your reverse was inside the loop)
    for (int v = t; v != -1; v = par[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    if (path.empty() || path.front() != s)
        return {};

    return path;
}

void Graph::printPath(const vector<int>& path)
{
    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << " -> ";
        cout << path[i];
    }
    cout << "\n";
}

size_t Graph::edgesCount() const
{
    size_t c=0; 
    for(int u=0;u<n_;++u) 
    {
        for(const auto &e: adj_[u]) 
        {
            if(e.cap<0) 
            {
                c++;
            }
        }
    }
    if(!directed_)
    {
        c/=2; 
    } 
    return c;
}

std::pair<std::vector<long long>, std::vector<int>>
Graph::dialSSSP(int s, int maxW) const
{
    const long long INF = (1LL<<60);
    std::vector<long long> dist(n_, INF);
    std::vector<int> parent(n_, -1);
    if (s < 0 || s >= n_) return {dist, parent};
    if (maxW <= 0) return {dist, parent}; // requires positive integer weights

    // Upper bound on smallest distances; K buckets (circular array not required here)
    int K = std::max(1, maxW * std::max(1, n_ - 1) + 1);
    std::vector<std::vector<int>> B(K);

    dist[s] = 0;
    B[0].push_back(s);
    int bucket = 0;
    int settled = 0;

    while (settled < n_) {
        while (bucket < K && B[bucket].empty()) ++bucket;
        if (bucket >= K) break;

        int u = B[bucket].back();
        B[bucket].pop_back();

        if (dist[u] != bucket) continue;  // stale entry
        ++settled;

        for (const auto& e : adj_[u]) if (e.cap < 0) { // normal (non-flow) edges
            if (e.w < 0 || e.w > maxW) continue;      // Dial requires 0..maxW
            long long nd = dist[u] + e.w;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = u;
                if (nd < K) B[(int)nd].push_back(e.to);
            }
        }
    }
    return {dist, parent};
}

std::vector<int> Graph::fleuryEulerTrailOrCircuit() const
{
    if (directed_) throw std::runtime_error("Fleury requires an undirected graph");

    // Build multigraph from normal edges (cap<0). Insert each undirected edge once.
    std::vector<std::multiset<int>> g(n_);
    int m = 0;
    for (int u = 0; u < n_; ++u) {
        for (const auto& e : adj_[u]) if (e.cap < 0) {
            int v = e.to;
            if (u <= v) { g[u].insert(v); g[v].insert(u); ++m; }
        }
    }
    if (m == 0) return {};

    auto firstNonIso = [&]()->int{
        for (int i=0;i<n_;++i) if (!g[i].empty()) return i;
        return -1;
    };

    // Connectivity check on non-isolated vertices
    {
        int s = firstNonIso();
        if (s == -1) return {};
        std::vector<char> vis(n_);
        std::stack<int> st; st.push(s); vis[s]=1;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            for (int v : g[u]) if (!vis[v]) { vis[v]=1; st.push(v); }
        }
        for (int i=0;i<n_;++i) {
            if (!g[i].empty() && !vis[i]) return {}; // disconnected positive-degree component
        }
    }

    // Count odd degrees
    auto deg = [&](int x){ return (int)g[x].size(); };
    int oddCnt=0, start=-1;
    for (int i=0;i<n_;++i) if (deg(i)%2) { ++oddCnt; if (start==-1) start=i; }
    if (!(oddCnt==0 || oddCnt==2)) return {};
    if (start==-1) start = firstNonIso();

    // Helpers
    auto reachable_count = [&](int src){
        std::vector<char> vis(n_);
        std::stack<int> st; st.push(src); vis[src]=1;
        int cnt=0;
        while (!st.empty()){
            int u = st.top(); st.pop(); ++cnt;
            // iterate over a snapshot to avoid iterator invalidation during checks
            std::vector<int> nbrs(g[u].begin(), g[u].end());
            for (int v : nbrs) if (!vis[v]) { vis[v]=1; st.push(v); }
        }
        return cnt;
    };

    auto isBridge = [&](int u,int v){
        if ((int)g[u].size()==1) return false; // only choice -> not a bridge
        int before = reachable_count(u);
        // remove u-v
        auto ituv = g[u].find(v); auto itvu = g[v].find(u);
        if (ituv==g[u].end() || itvu==g[v].end()) return false;
        g[u].erase(ituv); g[v].erase(itvu);
        int after  = reachable_count(u);
        // restore
        g[u].insert(v); g[v].insert(u);
        return (after < before);
    };

    std::vector<int> trail; trail.reserve(m+1);
    int u = start, remaining = m;
    while (remaining > 0) {
        // snapshot neighbors (avoid mutating while iterating)
        std::vector<int> nbrs(g[u].begin(), g[u].end());

        int chosen = -1;
        // Prefer a non-bridge if possible
        for (int v : nbrs) {
            if (!isBridge(u,v)) { chosen = v; break; }
        }
        if (chosen == -1) {
            // All are bridges; take the first available
            if (nbrs.empty()) return {}; // stranded (shouldn't happen in valid Euler case)
            chosen = nbrs[0];
        }

        // remove the chosen edge u-chosen
        auto ituv = g[u].find(chosen);
        auto itvu = g[chosen].find(u);
        g[u].erase(ituv); g[chosen].erase(itvu);
        --remaining;

        trail.push_back(u);
        u = chosen;
    }
    trail.push_back(u);
    return trail;
}




void Graph::printEulerResult() const {
    auto seq = fleuryEulerTrailOrCircuit();
    if (seq.empty()) { std::cout << "The graph does not have an Euler trail or circuit.\n"; return; }
    bool isCircuit = (seq.front() == seq.back());
    std::cout << "The graph has an Euler " << (isCircuit ? "circuit" : "trail") << ".\n";
    for (size_t i = 0; i < seq.size(); ++i) { if (i) std::cout << "->"; std::cout << seq[i]; }
    std::cout << "\n";
}
 

