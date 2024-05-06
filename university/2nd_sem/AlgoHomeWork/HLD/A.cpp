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
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'
int dfs1(const vector<vector<int>>& g, vector<int>& heavyEdge, vector<int>& depth, int cur)
{
    int weight = 1;
    int childW = 0;
    int child = 0;
    for(const auto& to : g[cur])
    {
        if(depth[to]) continue;

        depth[to] = depth[cur] + 1;
        int cur = dfs1(g, heavyEdge, depth, to);
        weight += cur;
        if(childW < cur)
        {
            childW = cur;
            child = to;
        }
    }
    heavyEdge[cur] = child;
    return weight;
}
void dfs2(const vector<vector<int>>& g, const vector<int>& heavyEdge, vector<int>& leader, vector<int>& parent, vector<int>& pos, int time, int cur, int prev)
{
    pos[cur] = time++;

    if(heavyEdge[cur])
    {
        parent[heavyEdge[cur]] = cur;
        leader[heavyEdge[cur]] = leader[cur];
        dfs2(g, heavyEdge, leader, parent, pos, time, heavyEdge[cur], cur);
    }

    for(auto&& to : g[cur])
    {
        if(to == heavyEdge[cur] || to == prev) continue;

        parent[to] = cur;
        leader[to] = to;
        dfs2(g, heavyEdge, leader, parent, pos, time, to, cur);
    }
}
class Tree
{
public:
    Tree(const vector<ll>& vec)
            : n(vec.size())
            , tree(n << 2, Node())
    {
        build(0, 0, n, vec);
    }
    Tree(int size_)
            : n(size_)
            , tree(n << 2, Node())
    {}

    void update(int l, int r, ll val)
    {
        update(0, l, r, 0, n, val);
    }

    ll getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
    ll getInPoint(int pos)
    {
        return getInPoint(0, 0, n, pos);
    }
private:
    struct Node
    {
        ll sum = 0;
        ll val = 0;
        bool push = false;
    };
    int n;
    vector<Node> tree;
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {vec[l], 0, false};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void push(int idx, int l, int r)
    {
        if(!tree[idx].push || l + 1 == r) return;

        int l_child = idx * 2 + 1, r_child = l_child + 1;

        int mid = (l + r) / 2;

        tree[l_child] = {tree[idx].val * (mid - l), tree[idx].val, true};
        tree[r_child] = {tree[idx].val * (r - mid), tree[idx].val, true};

        tree[idx].val = 0;
        tree[idx].push = false;
    }
    void update(int idx, int l, int r, int curL, int curR, ll val)
    {
        if(l >= r) return;


        if(l == curL && r == curR)
        {
            tree[idx] = {val * (r - l), val, true};
            return;
        }

        int mid = (curL + curR) >> 1;

        push(idx, curL, curR);

        update(idx * 2 + 1, l, min(mid, r), curL, mid, val);
        update(idx * 2 + 2, max(mid, l), r, mid, curR, val);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    ll getInPoint(int idx, int curL, int curR, int pos)
    {
        push(idx, curL, curR);

        if(curL + 1 == curR)
        {
            return tree[idx].sum;
        }

        int mid = (curL + curR) >> 1;

        if(pos < mid) return getInPoint(idx * 2 + 1, curL, mid, pos);
        else return getInPoint(idx * 2 + 2, mid, curR, pos);
    }
    ll getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;

        if(l == curL && r == curR)
        {
            return tree[idx].sum;
        }

        int mid = (curL + curR) / 2;

        push(idx, curL, curR);

        return getSum(idx * 2 + 1, l, min(r, mid), curL, mid) + getSum(idx * 2 + 2, max(l, mid), r, mid, curR);
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        g[from].eb(to);
        g[to].eb(from);
    }
    int root = 1;

    vector<int> depth(n + 1), heavyEdge(n + 1), leader(n + 1), parent(n + 1), pos(n + 1);
    depth[root] = 1;
    dfs1(g, heavyEdge, depth, root);
    leader[root] = root;
    dfs2(g, heavyEdge, leader, parent, pos, 0, root, -1);
    Tree ST(n);
    auto LCA = [&](int a, int b)
    {
        while(true)
        {
            if(leader[a] == leader[b]) return (depth[a] < depth[b]) ? a : b;
            if(depth[leader[a]] < depth[leader[b]])
            {
                b = parent[leader[b]];
            }
            else
            {
                a = parent[leader[a]];
            }
        }
    };

    auto get = [&](int a, int b)
    {
        int lca = LCA(a, b);
        ll res = 0;
        while(true)
        {
            if(leader[a] == leader[lca])
            {
                res += ST.getSum(pos[lca] + 1, pos[a] + 1);
                break;
            }

            res += ST.getSum(pos[leader[a]], pos[a] + 1);
            a = parent[leader[a]];
        }
        while(true)
        {
            if(leader[b] == leader[lca])
            {
                res += ST.getSum(pos[lca], pos[b] + 1);
                break;
            }

            res += ST.getSum(pos[leader[b]], pos[b] + 1);
            b = parent[leader[b]];
        }
        return res;
    };
    auto set = [&](int a, int b, int val)
    {
        int lca = LCA(a, b);
        while(true)
        {
            if(leader[a] == leader[lca])
            {
                ST.update(pos[lca] + 1, pos[a] + 1, val);
                break;
            }

            ST.update( pos[leader[a]], pos[a] + 1, val);
            a = parent[leader[a]];
        }
        while(true)
        {
            if(leader[b] == leader[lca])
            {
                ST.update(pos[lca], pos[b] + 1, val);
                break;
            }

            ST.update(pos[leader[b]], pos[b] + 1, val);
            b = parent[leader[b]];
        }
    };

    for(int i = 0; i < q; ++i)
    {
        int a1, b1, a2, b2;
        cin >> a1 >> b1 >> a2 >> b2;
//        cout << "LCA1 = " << LCA(a1, b1) << ", LCA2 = " << LCA(a2, b2) << endl;
        set(a1, b1, 1);
        cout << get(a2, b2) << endl;
        set(a1, b1, 0);
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