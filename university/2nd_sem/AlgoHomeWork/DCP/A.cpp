#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define eb emplace_back
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define ss second
#define ff first
//#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'
struct Change
{
    int v, parent, amount_of_unions;
    Change() = default;
    Change(int v, int parent, int amount_of_unions)
    : v(v), parent(parent), amount_of_unions(amount_of_unions) {}
};
class DSU
{
public:
    explicit DSU(size_t size, int indexation = 0)
    : n(size)
    , unionsCounter(n)
    , unionSize(n + indexation, 1)
    , parent(n + indexation, 0)
    {
        for(int i = indexation; i < n + indexation; ++i)
        {
            parent[i] = i;
        }
    }
    int getParent(int v)
    {
        if(parent[v] == v) return v;

        return getParent(parent[v]);
    }
    void unite(int a, int b, vector<Change>& history)
    {
        a = getParent(a);
        b = getParent(b);
        if(a == b) return;
        --unionsCounter;
        if(unionSize[a] > unionSize[b])
        {
            swap(a, b);
        }
        history.eb(a, parent[a], unionSize[b]);
        unionSize[b] += unionSize[a];
        parent[a] = b;
    }
    int& operator[](size_t idx)
    {
        return parent[idx];
    }
    bool areInTheSameUnion(int a, int b)
    {
        return getParent(a) == getParent(b);
    }
    size_t& unionsAmount()
    {
        return unionsCounter;
    }
private:
    size_t n;
    size_t unionsCounter;
    vector<int> unionSize;
    vector<int> parent;
};
class Edge
{
public:
    int from, to;
    bool operator<(const Edge& other) const
    {
        return (from != other.from) ? from < other.from : to < other.to;
    }
};
class Event
{
public:
    Edge edge;
    int l, r;
};
class DCP_Tree
{
public:
    struct Node
    {
        vector<Change> history;
        vector<Edge> edges;
    };
    explicit DCP_Tree(int events_counter)
    : n(events_counter)
    , tree(n << 2, Node()) {}
    void addEdge(int l, int r, const Edge& edge)
    {
        addEdge(0, 0, n, l, r, edge);
    }
    void go(int idx, int l, int r, DSU& dsu, const vector<bool>& questions)
    {
        if(l + 1 == r)
        {
            if(questions[l]) cout << dsu.unionsAmount() << endl;
            return;
        }

        for(auto& [from, to] : tree[idx].edges)
        {
            dsu.unite(from, to, tree[idx].history);
        }

        int mid = (l + r) >> 1;
        go(idx * 2 + 1, l, mid, dsu, questions);
        go(idx * 2 + 2, mid, r, dsu, questions);

        previousVersion(idx, dsu);
    }
private:
    int n;
    vector<Node> tree;
    void addEdge(int idx, int curL, int curR, int l, int r, const Edge& edge)
    {
        if(l >= r) return;

        if(curL == l && curR == r)
        {
            tree[idx].edges.emplace_back(edge);
            return;
        }

        int mid = (curL + curR) >> 1;

        addEdge(idx * 2 + 1, curL, mid, l, min(r, mid), edge);
        addEdge(idx * 2 + 2, mid, curR, max(l, mid), r, edge);
    }
    void previousVersion(int idx, DSU& dsu)
    {
        auto& history = tree[idx].history;
        for(int i = 0; i < history.size(); ++i)
        {
            auto& v = history[i].v;
            auto& parent = history[i].parent;
            auto& size = history[i].amount_of_unions;
            dsu[v] = parent;
            dsu.unionsAmount() = size;
        }
        history.clear();
    }
};
void solve()
{
    int n, k;
    cin >> n >> k;
    map<Edge, int> notDeletedEdges;
    vector<int> questions(k + 1);
    DCP_Tree ST(k + 1);
    for(int i = 1; i < k + 1; ++i)
    {
        char action;
        cin >> action;
        if(action == '?') questions[i] = true;
        else
        {
            Edge edge;
            cin >> edge.from >> edge.to;
            if(notDeletedEdges[edge])
            {
                ST.addEdge(notDeletedEdges[edge], i + 1, edge);
                notDeletedEdges.erase(edge);
            }
            else
            {
                notDeletedEdges[edge] = i;
            }
        }
    }
    for(auto&& [edge, time] : notDeletedEdges)
    {
        ST.addEdge(time, k + 1, edge);
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}