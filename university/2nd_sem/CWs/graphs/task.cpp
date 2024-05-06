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
void dfs(vector<vector<int>>& g, vector<ll>& st, vector<int>& tin, vector<int>& tout, int cur, int prev, int& time)
{
    tin[cur] = time++;
    st.pb(cur);
    for(const auto& to : g[cur])
    {
        if(to == prev) continue;

        dfs(g, st, tin, tout, to, cur, time);
    }
    tout[cur] = time;
}
void precomp(const vector<vector<int>>& g, vector<vector<int>>& up, vector<int>& tin, vector<int>& tout, int v, int prev)
{
    for (int l = 1; l < 30; ++l)
    {
        up[v][l] = up[up[v][l - 1]][l - 1];
    }
    for (const auto& u : g[v])
    {
        if (u != prev)
        {
            up[u][0] = v;
            precomp(g, up, tin, tout, u, v);
        }
    }
}
bool IsAncestor(int a, int b, const vector<int>& tin, const vector<int>& tout)
{
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}
int LCA(int a, int b, const vector<int>& tin, const vector<int>& tout, const vector<vector<int>>& up)
{
    if (IsAncestor(a, b, tin, tout))
    {
        return a;
    }
    if (IsAncestor(b, a, tin, tout))
    {
        return b;
    }
    for (int l = 29; l >= 0; --l)
    {
        if (!IsAncestor(up[a][l], b, tin, tout))
        {
            a = up[a][l];
        }
    }
    return up[a][0];
}
template<typename T>
struct SumAddTree
{
    SumAddTree(size_t size, T def = (T) 0)
            : n(size)
            , def(def)
    {
        tree.assign(n * 4, Node());
        build(0, 0, n);
    }
    SumAddTree(const vector<T>& vec, const vector<ll>& w)
            : n(vec.size())
    {
        tree.assign(n * 4, Node());
        build(0, 0, n, vec, w);
    }
    void update(int l, int r, T val)
    {
        update(0, l, r, val, 0, n);
    }
    T getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
private:
    struct Node
    {
        T dif = 0;
        T sum = 0;
    };
    int n;
    T def;
    vector<Node> tree;
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = def;
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void build(int idx, int l, int r, const vector<T>& vec, const vector<ll>& w)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = w[vec[l]];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec, w);
        build(idx * 2 + 2, mid, r, vec, w);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum;
    }
    void update(int idx, int l , int r, T val, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].dif += val;
            tree[idx].sum += val * (r - l);
            return;
        }

        int mid = (curL + curR) / 2;

        update(idx * 2 + 1, l, min(mid, r), val, curL, mid);
        update(idx * 2 + 2, max(mid, l), r, val, mid, curR);

        tree[idx].sum = tree[idx * 2 + 1].sum + tree[idx * 2 + 2].sum + tree[idx].dif * (curR - curL);
    }
    T getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;
        if(l == curL && r == curR)
        {
            return tree[idx].sum;
        }

        int mid = (curL + curR) / 2;

        return getSum(idx * 2 + 1, l, min(r, mid), curL, mid) + getSum(idx * 2 + 2, max(l, mid), r, mid, curR) + tree[idx].dif * (r - l);
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ll> weights(n);
    input(weights);
    vector<vector<int>> g(n);
    vector<int> parent(n);
    for(int i = 0; i < n - 1; ++i)
    {
        int from, to;
        cin >> from >> to;
        parent[to] = from;
        g[from].pb(to);
        g[to].pb(from);
    }
    vector<ll> st;
    vector<int> tin(n);
    vector<int> tout(n);
    int time = 0;
    dfs(g, st, tin, tout, 1, -1, time);
    vector<vector<int>> up(30, vector<int> (n));
    precomp(g, up, tin, tout, 0, -1);

    SumAddTree<ll> ST(st, weights);

    int q;
    cin >> q;
    while(q--)
    {
        int type;
        cin >> type;
        int k;
        cin >> k;
        ll x;
        cin >> x;
        stack<int> v;
        for(int i = 0; i < k; ++i)
        {
            int b;
            cin >> b;
            v.push(b);
        }
        while(v.size() != 1)
        {
            int cur1 = v.top();
            v.pop();
            int cur2 = v.top();
            v.pop();
            int lca = LCA(cur1, cur2, tin, tout, up);
            v.push(lca);
        }
        int lca = v.top();
        if(type == 1)
        {
            ST.update(tin[lca], tout[lca], x);
        }
        else
        {
            cout << ST.getSum(tin[lca], tout[lca]) << endl;
        }
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