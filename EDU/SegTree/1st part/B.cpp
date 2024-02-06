#include <bits/stdc++.h>
using namespace std;
using ll = int;
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
  
int MOD;

void printMat(vector<int>& mat)
{
    cout << mat[0] << ' ' << mat[1] << '\n' << mat[2] << ' ' << mat[3] << endl << endl;
}
struct SumTree
{
    vector<int> def = {1, 0, 0, 1};
    
    SumTree(const vector<vector<int>>& vec)
    {
        n = vec.size();
        tree.assign(n * 4, def);
        build(vec);
    }
    SumTree(size_t size)
    {
        n = size;
        tree.assign(4 * n, def);
    }
    void build(const vector<vector<int>>& vec)
    {
        build(0, 0, n, vec);
    }
    vector<int> getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
    
private:
    int n;
    vector<vector<int>> tree;
    vector<int> combine(vector<int> a, vector<int> b)
    {
        vector<int> ab(4);
        ab[0] = (a[0] * b[0] + a[1] * b[2]) % MOD;
        ab[1] = (a[0] * b[1] + a[1] * b[3]) % MOD;
        ab[2] = (a[2] * b[0] + a[3] * b[2]) % MOD;
        ab[3] = (a[2] * b[1] + a[3] * b[3]) % MOD;
        return ab;
    }
    void build(int idx, int l, int r, const vector<vector<int>>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = vec[l];
            // cout << "idx = " << idx << ", l = " << l << ", r = " << r - 1 << ":" << endl;
            // printMat(tree[idx].matrix);
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = combine(tree[idx * 2 + 1], tree[idx * 2 + 2]);
        // cout << "idx = " << idx << ", l = " << l << ", r = " << r - 1 << ":" << endl;
        // printMat(tree[idx].matrix);
    }
    vector<int> getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return def;
        if(l == curL && r == curR) return tree[idx];
        
        int mid = (curL + curR) / 2;

        return combine(getSum(idx * 2 + 1, l, min(r, mid), curL, mid), getSum(idx * 2 + 2, max(l, mid), r, mid, curR));
    }
    
};
void solve()
{
    int n, m;
    cin >> MOD >> n >> m;
    // cout << n << ' ' << m << endl;
    vector<vector<int>> vec(n, vector<int>(4));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            cin >> vec[i][j];
        }
    }
    // cout << "product [2, 3] = " << endl;
    // auto res = product({{1, 1}, {1, 1}}, vec[2]);
    // printMat(res);
    
    // cout << "matrixes were read" << endl;
    SumTree ST(vec);
    for(int i = 0; i < m; ++i)
    {
        int l, r;
        cin >> l >> r;
        auto res = ST.getSum(l - 1, r);
        // cout << "query No" << i + 1 << ":" << endl;
        printMat(res);
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