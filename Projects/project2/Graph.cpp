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



// Extract integer after "label=" (quoted or not). Returns 1 if not found.
static long long extract_label_weight(const std::string& attrs) {
    size_t p = attrs.find("label");
    if (p == std::string::npos) return 1;
    p = attrs.find('=', p);
    if (p == std::string::npos) return 1;
    ++p;
    while (p < attrs.size() && std::isspace((unsigned char)attrs[p])) ++p;
    if (p < attrs.size() && (attrs[p] == '"' || attrs[p] == '\'')) ++p;
    bool neg = false;
    if (p < attrs.size() && (attrs[p] == '-' || attrs[p] == '+')) { neg = attrs[p] == '-'; ++p; }
    long long val = 0; bool any=false;
    while (p < attrs.size() && std::isdigit((unsigned char)attrs[p])) { any=true; val = val*10 + (attrs[p]-'0'); ++p; }
    if (!any) return 1;
    return neg ? -val : val;
}

Graph Graph::readDOT(const string& filename) {
    ifstream in(filename);
    if (!in) throw runtime_error("Cannot open " + filename);

    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    bool directed = content.find("digraph") != string::npos;

    Graph g(0, directed);

    // ... your robust edge regex that captures attribute list and extracts label ...

    std::regex edgeRe(R"(([0-9]+)\s*(->|--)\s*([0-9]+)\s*(\[([^\]]*)\])?)");
    auto it = std::sregex_iterator(content.begin(), content.end(), edgeRe), ed = std::sregex_iterator();
    for (; it != ed; ++it) {
        int u = stoi((*it)[1]);
        int v = stoi((*it)[3]);

        // If undirected, only add once (let addEdge create the reverse).
        if (!directed && u > v) continue;

        long long val = 1;
        if ((*it)[5].matched) {
            const string attrs = (*it)[5].str();
            val = extract_label_weight(attrs); // your helper
        }

        // If this DOT is a flow graph, call addEdge(u,v,0,val); otherwise addEdge(u,v,val);
        g.addEdge(u, v, val);  // or g.addEdge(u,v,0,val) when label is capacity
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
