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
#define int int64_t


inline vector<ll> matrixProduct(int n1, int m1, int n2, int m2, const vector<ll>& a, const vector<ll>& b, const ll MOD = 1'000'000'007)
{
    assert(n2 == m1);
    
    int n = n1, m = m2;

    vector<ll> mat(n * m);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            for(int k = 0; k < n2; ++k)
            {
                mat[j + i * n] += (a[k + i * m1] * b[j + k * n2]) % MOD;
                mat[j + i * n] %= MOD;
            }
        }
    }

    return mat;
}

inline vector<ll> matrixBinPow(int num, size_t size, const vector<ll>& mat, unordered_map<int, vector<ll>>& power, const ll MOD = 1'000'000'007)
{
    if(num == 1) return mat;
    // if(power.contains(num)) return power[num];
    vector<ll> ans (size * size);
    for(int i = 0; i < size; ++i) ans[i + i * size] = 1;

    vector<ll> cur = mat;

    while(num)
    {
        if(num & 1) ans = matrixProduct(size, size, size, size, ans, cur);
        cur = matrixProduct(size, size, size, size, cur, cur);
        num >>= 1;
    }
    power[num] = ans;
    assert(power[num] == ans);
    return ans;
}

inline vector<ll> matrixAddition(int n1, int m1, int n2, int m2, const vector<ll>& a, const vector<ll>& b, const ll MOD = 1'000'000'007)
{
    assert(n1 == n2 && m1 == m2);

    vector<ll> ans(n1 * m1);
    
    for(int i = 0; i < n1; ++i)
    {
        for(int j = 0; j < m2; ++j)
        {
            ans[j + i * n1] = (a[j + i * n1] + b[j + i * n1]) % MOD;
        }
    }

    return ans;
}
inline vector<ll> fastFib(int num, const ll MOD = 1e9 + 7)
{
    num -= 1;
    vector<ll> ans = {1, 0, 0, 1};
    vector<ll> cur = {0, 1, 1, 1};
    while(num)
    {
        if(num & 1) ans = matrixProduct(2, 2, 2, 2, ans, cur);
        cur = matrixProduct(2, 2, 2, 2, cur, cur);
        num >>= 1;
    }
    vector<ll> fib = {0, 1};
    return matrixProduct(1, 2, 2, 2, fib, ans);
}

struct FibTree
{
    FibTree(const vector<ll>& vec)
    : n(vec.size())
    {
        tree.assign(n * 4, Node());
        build(0, 0, n, vec);
        // cerr << "Tree was created" << '\n';
        // cerr.flush();
    }
    void update(int l, int r, ll val)
    {
        update(0, l, r, val, 0, n);
    }
    ll getFib(int l, int r)
    {
        return getFib(0, l, r, 0, n)[1];
    }
private:
    struct Node
    {
        ll val = 0;
        vector<ll> mat = {0, 1};
    };
    int n;
    const vector<ll> p = {0, 1, 1, 1};
    vector<Node> tree;
    unordered_map<int, vector<ll>> power;
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].val = 0;
            tree[idx].mat = fastFib(vec[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx].mat = matrixAddition(1, 2, 1, 2, tree[idx * 2 + 1].mat, tree[idx * 2 + 2].mat);
    }
    inline void update(int idx, int l, int r, ll val, int curL, int curR)
    {
        if(l >= r) return;

        if(l == curL && r == curR)
        {
            tree[idx].val += val;
            tree[idx].mat = matrixProduct(1, 2, 2, 2, tree[idx].mat, matrixBinPow(val, 2, p, power));
            return;
        }

        int mid = (curL + curR) / 2;

        update(idx * 2 + 1, l, min(r, mid), val, curL, mid);
        update(idx * 2 + 2, max(l, mid), r, val, mid, curR);

        tree[idx].mat = matrixAddition(1, 2, 1, 2, tree[idx * 2 + 1].mat, tree[idx * 2 + 2].mat);
        tree[idx].mat = matrixProduct(1, 2, 2, 2, tree[idx].mat, matrixBinPow(tree[idx].val, 2, p, power));
    }

    inline vector<ll> getFib(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return {0, 0};
        if(l == curL && r == curR)
        {
            return tree[idx].mat;
        }
        int mid = (curL + curR) / 2;

        return matrixProduct(1, 2, 2, 2, matrixAddition(1, 2, 1, 2, getFib(idx * 2 + 1, l, min(r, mid), curL, mid), getFib(idx * 2 + 2, max(l, mid), r, mid, curR)), matrixBinPow(tree[idx].val, 2, p, power));
    } 

};
inline void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    FibTree ST(vec);
    // for(int i = 0; i <= n; ++i)
    // {
    //     for(int j = i + 1; j <= n; ++j)
    //     {
    //         cout << "l = " << i + 1 << ", r = " << j << "; sum by ST = " << ST.getFib(i, j) << ", sum = " << j - i << endl;
    //         cout.flush();
    //         assert(ST.getFib(i, j) == j - i);
    //     }
    // }
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;

        if(type == 1)
        {
            int l, r;
            ll val;
            cin >> l >> r >> val;
            ST.update(l - 1, r, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << ST.getFib(l - 1, r) << endl;
        }
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}