#include "Graph.h"
//using namespace std;

namespace 
{
    struct DisjointSet 
    {
        std::vector<int> p, r;
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
                std::swap(a,b);
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



Graph::Graph(int n, bool directed): n_(n), directed_(directed) 
{ 
    adj_.assign(n_, {}); 
}



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



void Graph::addEdge(int u, int v, long long w, std::optional<long long> cap)
{
    ensureVertex(std::max(u,v));
    if(cap.has_value())
    {
        // Flow edge 
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



bool Graph::hasPathDFS(int s, int t) const
{
    if(s<0||t<0||s>=n_||t>=n_)
    {
        return false;
    } 
    std::vector<char> vis(n_);
    std::stack<int> st; 
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
    std::vector<char> vis(n_);
    std::queue<int> q;
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



std::pair<bool, std::vector<int>> Graph::findCycleDirected() const
{
    std::vector<int> color(n_,0), par(n_,-1), cyc; 
    int start=-1, end=-1;
    std::function<bool(int)> dfs = [&](int u)
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



std::vector<int> Graph::topoSort() const
{
    std::vector<int> indeg(n_,0);
    
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
    std::queue<int> q; 
    
    for(int i=0;i<n_;++i)
    {
        if(indeg[i]==0) 
        {
            q.push(i);
        }
    } 
    std::vector<int> order; 
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
        throw std::runtime_error("Graph has cycles; topological sort undefined");
    } 

    return order;
}



std::pair<std::vector<int>, std::vector<int>> Graph::unweightedSSSP(int s) const
{
    const int INF=1e9; 
    std::vector<int> dist(n_,INF), par(n_,-1); 
    
    if(s<0||s>=n_)
    {
        return {dist,par};
    } 
    std::queue<int> q; 
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



std::pair<std::vector<long long>, std::vector<int>> Graph::dijkstra(int s) const
{
    const long long INF=(1LL<<60); 
    std::vector<long long> d(n_,INF); 
    std::vector<int> par(n_,-1);
    
    if(s<0||s>=n_)
    {
        return {d,par};
    } 
    using P=std::pair<long long,int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
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



std::vector<std::vector<long long>> Graph::floydWarshall(long long INF) const
{
    std::vector<std::vector<long long>> D(n_, std::vector<long long>(n_, INF));
    
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
                D[u][e.to]=std::min(D[u][e.to], e.w>=0?e.w:1LL);
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
                        D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
                    }
                }
            }
            
        } 
    }
        
    return D;
}



long long Graph::maxFlowEdmondsKarp(int s, int t)
{
    std::vector<std::vector<Edge>> res(n_);
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
        std::vector<int> parV(n_,-1), parE(n_,-1);
        std::queue<int> q; 
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
            break; // no aug
        } 
        long long aug=LLONG_MAX;

        for(int v=t; v!=s; v=parV[v])
        { 
            auto &e=res[parV[v]][parE[v]]; 
            aug=std::min(aug, e.cap); 
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



std::pair<long long, std::vector<std::tuple<int,int,long long>>> Graph::primMST(int start) const
{
    if(directed_)
    {
        throw std::runtime_error("Prim requires an undirected graph");
    } 
    
    if(n_==0) 
    {
        return {0,{}};
    }

    std::vector<char> vis(n_,0); 
    using T=std::tuple<long long,int,int>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

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
    std::vector<std::tuple<int,int,long long>> edges; 
    edges.reserve(n_?n_-1:0);
    
    while(!pq.empty() && (int)edges.size()<std::max(0,n_-1))
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
    
    if((int)edges.size()!=std::max(0,n_-1)) 
    {
        throw std::runtime_error("Graph is disconnected; MST not complete");
    }
    
    return {cost, edges};
}



std::pair<long long, std::vector<std::tuple<int,int,long long>>> Graph::kruskalMST() const
{
    if(directed_) 
    {
        throw std::runtime_error("Kruskal requires an undirected graph");
    }
    struct E{int u,v; long long w;}; 
    std::vector<E> es; 
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
    std::vector<std::tuple<int,int,long long>> ans; 
    ans.reserve(n_?n_-1:0);
    
    for(auto &e: es)
    { 
        if(ds.unite(e.u,e.v))
        { 
            cost+=e.w; 
            ans.emplace_back(e.u,e.v,e.w);
        } 
    }
    
    if((int)ans.size()!=std::max(0,n_-1)) 
    {
        throw std::runtime_error("Graph is disconnected; forest built");
    }
    
    return {cost, ans};
}



static long long extract_label_weight(const std::string& attrs) 
{
    std::regex labRe(R"(label\s*=\s*\"?(-?\d+)\"?)");
    std::smatch m;
    if (std::regex_search(attrs, m, labRe)) 
    {
        return std::stoll(m[1]);
    }

    return 1;
}



Graph Graph::readDirectedDOT(const std::string& filename, bool labelIsCapacity)
{
    std::ifstream in(filename);
    if (!in)
    {
        throw std::runtime_error("Cannot open " + filename);
    }

    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    Graph g(0, /*directed=*/true);
    std::regex edgeRe(R"(([0-9]+)\s*->\s*([0-9]+)\s*(?:\[([^\]]*)\])?)");
    std::set<std::tuple<int,int,long long>> seen;

    for (std::sregex_iterator it(content.begin(), content.end(), edgeRe), ed; it != ed; ++it) 
    {
        int u = std::stoi((*it)[1]);
        int v = std::stoi((*it)[2]);

        long long val = 1; 
        
        if ((*it)[3].matched) 
        {
            const std::string attrs = (*it)[3].str();
            val = extract_label_weight(attrs);
        }
        auto key = std::make_tuple(u, v, val);
        
        if (!seen.insert(key).second)
        {
            continue;
        }

        if (labelIsCapacity) 
        {
            g.addEdge(u, v, /*w=*/0, /*cap=*/val);
        } 

        else 
        {
            g.addEdge(u, v, /*w=*/val);
        }
    }

    return g;
}



Graph Graph::readUndirectedDOT(const std::string& filename)
{
    std::ifstream in(filename);
    if(!in)
    {
        throw std::runtime_error("Cannot open " + filename);
    }
    std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    Graph g(0, false); // undirected = false
    std::regex edgeRe(R"(([0-9]+)\s*--\s*([0-9]+)\s*(?:\[\s*label\s*=\s*\"?(-?[0-9]+)\"?\s*\])?)");
    auto it = std::sregex_iterator(content.begin(), content.end(), edgeRe);
    auto end = std::sregex_iterator();

    std::set<std::pair<int,int>> seen; // to avoid duplicates

    for(; it != end; ++it)
    {
        int u = stoi((*it)[1]);
        int v = stoi((*it)[2]);
        long long w = (*it)[3].matched ? stoll((*it)[3]) : 1;
        std::pair<int,int> key = (u < v) ? std::make_pair(u,v) : std::make_pair(v,u);

        if(seen.count(key))
        {
            continue;
        }
        seen.insert(key);
        g.addEdge(u, v, w);
    }

    return g;
}



void Graph::loadFromDOT(const std::string& filename, bool directed, bool labelIsCapacity)
{
    Graph tmp = directed
        ? Graph::readDirectedDOT(filename, labelIsCapacity)
        : Graph::readUndirectedDOT(filename);
    *this = std::move(tmp);
}



void Graph::writeLastFlowDOT(const std::string& filename) const
{
    if (lastResidual_.empty())
    {
        throw std::runtime_error("Run maxFlowEdmondsKarp first");
    }
    std::ofstream out(filename);
    
    if (!out)
    {
        throw std::runtime_error("Cannot open " + filename);
    }
    out << "strict digraph \"Flow Graph\" {\n\n    rankdir=LR;\n";

    for (int u = 0; u < n_; ++u)
    {
        for (const auto& orig : adj_[u])
        {
            if (orig.cap < 0) 
            {
                continue;  // only flow 
            }
            const int v = orig.to;
            const long long cap = orig.cap;
            long long flow = 0;

            for (const auto& re : lastResidual_[u])
            {
                if (re.to == v)
                {
                    flow = lastResidual_[v][re.rev].cap;
                    break;
                }
            }

            if (cap == 0)
            {
                out << "    " << u << " -> " << v << "\n";
                continue;
            }
            out << "    " << u << " -> " << v << " [label=\"" << flow << "/" << cap << "\"]\n";
        }
    }

    out << "}\n";
}



std::vector<int> Graph::restorePath(int s, int t, const std::vector<int>& par)
{
    std::vector<int> path;
    if (t < 0 || t >= (int)par.size())
    {
        return path;
    }

    if (s == t) 
    {                
        path.push_back(s);
        return path;
    }

    if (par[t] == -1)// no path
    {
        return path;
    }

    for (int v = t; v != -1; v = par[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());

    if (path.empty() || path.front() != s)
    {
        return {};
    }

    return path;
}



void Graph::printPath(const std::vector<int>& path)
{
    for (size_t i = 0; i < path.size(); ++i) 
    {
        if (i) std::cout << " -> ";
        std::cout << path[i];
    }
    std::cout << "\n";
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



std::pair<std::vector<long long>, std::vector<int>> Graph::dialSSSP(int s, int maxW) const
{
    const long long INF = (1LL<<60);
    std::vector<long long> dist(n_, INF);
    std::vector<int> parent(n_, -1);
    if (s < 0 || s >= n_) 
    {
        return {dist, parent};
    }
    if (maxW <= 0)
    {
        return {dist, parent}; 
    }

    int K = std::max(1, maxW * std::max(1, n_ - 1) + 1);
    std::vector<std::vector<int>> B(K);
    dist[s] = 0;
    B[0].push_back(s);
    int bucket = 0;
    int settled = 0;

    while (settled < n_) 
    {
        while (bucket < K && B[bucket].empty())
        {
            ++bucket;
        }

        if (bucket >= K) 
        {
            break;
        }
        int u = B[bucket].back();
        B[bucket].pop_back();
        if (dist[u] != bucket) 
        {
            continue;
        }
        ++settled;

        for (const auto& e : adj_[u]) if (e.cap < 0) 
        {
            if (e.w < 0 || e.w > maxW) 
            {
                continue;  
            }
            long long nd = dist[u] + e.w;
            
            if (nd < dist[e.to]) 
            {
                dist[e.to] = nd;
                parent[e.to] = u;
                if (nd < K)
                {
                    B[(int)nd].push_back(e.to);
                }
            }
        }
    }

    return {dist, parent};
}



std::vector<int> Graph::fleuryEulerTrailOrCircuit() const
{
    if (directed_) 
    {
        throw std::runtime_error("Fleury requires an undirected graph");
    }
    std::vector<std::multiset<int>> g(n_);
    int m = 0;
    
    for (int u = 0; u < n_; ++u) 
    {
        for (const auto& e : adj_[u])
        {
            if (e.cap < 0) 
            {
                int v = e.to;
                if (u <= v) 
                { 
                    g[u].insert(v); 
                    g[v].insert(u); 
                    ++m; 
                }
            }
        }   
    }

    if (m == 0) 
    {
        return {};
    }

    auto firstNonIso = [&]()->int
    {
        for (int i=0;i<n_;++i) 
        {
            if(!g[i].empty())
            {
                return i;
            }
        }
        return -1;
    };
    {
        int s = firstNonIso();
        if (s == -1) 
        {
            return {};
        }
        std::vector<char> vis(n_);
        std::stack<int> st; 
        st.push(s); 
        vis[s]=1;
        
        while (!st.empty()) 
        {
            int u = st.top(); 
            st.pop();
            for (int v : g[u]) 
            {
                if(!vis[v]) 
                {
                    vis[v]=1; 
                    st.push(v); 
                }
            }
        }
        for (int i=0;i<n_;++i) 
        {
            if(!g[i].empty() && !vis[i]) 
            {
                return {};
            }
        }
    }

    // Count odd degrees
    auto deg = [&](int x)
    { 
        return (int)g[x].size(); 
    };
    int oddCnt=0, start=-1;

    for (int i=0;i<n_;++i) 
    {
        if(deg(i)%2) 
        { 
            ++oddCnt; 
            if (start==-1) 
            {
                start=i;
            } 
        }
    }

    if (!(oddCnt==0 || oddCnt==2)) 
    {
        return {};
    }

    if (start==-1)
    {
        start = firstNonIso();
    }

    auto reachable_count = [&](int src)
    {
        std::vector<char> vis(n_);
        std::stack<int> st; 
        st.push(src); 
        vis[src]=1;
        int cnt=0;

        while (!st.empty())
        {
            int u = st.top(); 
            st.pop(); 
            ++cnt;
            std::vector<int> nbrs(g[u].begin(), g[u].end());
            for (int v : nbrs)
            { 
                if(!vis[v]) 
                { 
                    vis[v]=1; 
                    st.push(v); 
                }
            }
        }

        return cnt;
    };

    auto isBridge = [&](int u,int v)
    {
        if ((int)g[u].size()==1) 
        {
            return false; 
        }
        int before = reachable_count(u);
        auto ituv = g[u].find(v); 
        auto itvu = g[v].find(u);
        if (ituv==g[u].end() || itvu==g[v].end()) 
        {
            return false;
        }
        g[u].erase(ituv); 
        g[v].erase(itvu);
        int after  = reachable_count(u);
        g[u].insert(v); 
        g[v].insert(u);
        return (after < before);
    };

    std::vector<int> trail; 
    trail.reserve(m+1);
    int u = start, remaining = m;
    while (remaining > 0) 
    {
        std::vector<int> nbrs(g[u].begin(), g[u].end());
        int chosen = -1;
        for (int v : nbrs) 
        {
            if (!isBridge(u,v)) 
            { 
                chosen = v; 
                break; 
            }
        }

        if (chosen == -1) 
        {
            if (nbrs.empty()) 
            {
                return {}; 
            }
            chosen = nbrs[0];
        }

        auto ituv = g[u].find(chosen);
        auto itvu = g[chosen].find(u);
        g[u].erase(ituv); 
        g[chosen].erase(itvu);
        --remaining;
        trail.push_back(u);
        u = chosen;
    }
    trail.push_back(u);

    return trail;
}



void Graph::printEulerResult() const 
{
    auto seq = fleuryEulerTrailOrCircuit();
    if (seq.empty()) 
    { 
        std::cout << "The graph does not have an Euler trail or circuit.\n"; 
        return; 
    }
    bool isCircuit = (seq.front() == seq.back());
    std::cout << "The graph has an Euler " << (isCircuit ? "circuit" : "trail") << ".\n";
    for (size_t i = 0; i < seq.size(); ++i) 
    { 
        if (i) 
        {
            std::cout << "->";
        } 
        std::cout << seq[i]; 
    }
    std::cout << "\n";
}



bool Graph::writePNG(const std::string& dotFile, const std::string& pngFile) const
{
    std::string cmd = "dot -Tpng \"" + dotFile + "\" -o \"" + pngFile + "\"";
    int result = system(cmd.c_str());

    if (result != 0) 
    {
        std::cerr << "Error: Failed to generate PNG. Make sure Graphviz is installed.\n";
        return false;
    }

    return true;
}



void Graph::writeDOTDirectedStrict(const std::string& filename, const std::string& title) const
{
    std::ofstream out(filename);
    if (!out) 
    {
        throw std::runtime_error("Cannot open " + filename);
    }

    out << "strict digraph \"" << (title.empty() ? "DirectedGraph" : title) << "\" {\n";
    out << "    rankdir=LR;\n\n";

    for (int u = 0; u < n_; ++u)
    {
        std::vector<Edge> sorted = adj_[u];
        std::sort(sorted.begin(), sorted.end(), [](const Edge& a, const Edge& b)
        {
            if (a.to != b.to) 
            {
                return a.to < b.to;
            }
            return a.cap < b.cap;
        }
        );

        for (const auto& e : sorted)
        {
            if (e.cap == 0) 
            {
                continue;
            }
            long long lbl = e.cap;                 
            if (lbl < 0) lbl = 1;            

            out << "    " << u << " -> " << e.to << " [label=\"" << lbl << "\"];\n";
        }
    }

    out << "}\n";
}



void Graph::writeDOTUndirectedExpanded(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open " + filename);
    out << "graph {\n";
    out << "        rankdir=LR;\n";
    std::set<std::pair<int,int>> emitted;

    for (int u = 0; u < n_; ++u)
    {
        std::vector<Edge> sorted = adj_[u];
        std::sort(sorted.begin(), sorted.end(), [](const Edge& a, const Edge& b)
        {
            if (a.to != b.to) 
            {
                return a.to < b.to;
            }
            return a.w < b.w;
        }
        );

        for (const auto& e : sorted)
        {
            if (e.cap == 0) 
            {
                continue;
            }  

            int a = std::min(u, e.to), b = std::max(u, e.to);
            if (!emitted.insert({a, b}).second)      
            {
                continue;
            }
            long long lbl = e.w;                     
            if (lbl < 0) 
            {
                lbl = 1;                    
            }
            out << "        " << a << " -- " << b << " [label=\"" << lbl << "\"]\n";
        }
    }

    out << "}\n";
}



void Graph::writeDOT(const std::string& filename, const std::string& title, bool directed) const
{
    if (directed) 
    {
        writeDOTDirectedStrict(filename, title);
    }
    else
    {
        writeDOTUndirectedExpanded(filename);
    }
}



void Graph::writeEulerTraversalDOT(const std::string& dotFile) const
{
    if (directed_) 
    {
        throw std::runtime_error("Euler traversal DOT requires an undirected graph");
    }
    std::vector<int> seq = fleuryEulerTrailOrCircuit();
    
    if (seq.empty()) 
    {
        throw std::runtime_error("No Euler trail/circuit exists to write");
    }
    std::ofstream out(dotFile);
    if (!out) 
    {
        throw std::runtime_error("Cannot open " + dotFile);
    }
    out << "graph {\n";
    out << "    rankdir=LR;\n";

    for (size_t i = 0; i + 1 < seq.size(); ++i)
    {
        int u = seq[i], v = seq[i+1];
        int a = std::min(u, v), b = std::max(u, v);
        out << "    " << a << " -- " << b << " [label=\"" << (i + 1) << "\"]\n";
    }

    out << "}\n";
}