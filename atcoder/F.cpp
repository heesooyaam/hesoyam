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
// #define mp make_pair
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define make_unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define endl '\n'   
struct Tree
{
    Tree(vector<ll>& vec)
    : n(vec.size())
    , vec(vec)
    {
        tree.resize(4 * n, {});
        build(0, 0, n);
    }
    void update(int pos, ll val)
    {
        update(0, pos, val, 0, n);
        vec[pos] = val;
    }
    ll get(int l, int r)
    {
        auto res = get(0, l, r, 0, n);
        return (res.ff.ff != 0) ? res.ff.ss : 0;
    }
private:
    int n;
    vector<map<ll, int>> tree;
    vector<ll>& vec;
    void update(int idx, int pos, ll val, int l, int r)
    {
        if(l + 1 == r)
        {
            auto it = tree[idx].find(vec[pos]);
            if(it->ss == 1) tree[idx].erase(it);
            else it->ss -= 1;

            tree[idx][val] += 1;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos < mid)
        {
            update(idx * 2 + 1, pos, val, l, mid);
        }
        else{
            update(idx * 2 + 2, pos, val, mid, r);
        }
        auto it = tree[idx].find(vec[pos]);
        if(it->ss == 1) tree[idx].erase(it);
        else it->ss -= 1;
        tree[idx][val] += 1;
    }
    pair<pair<int, int>, pair<int, int>> combine(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b)
    {
        int MX1, MX2;
        MX1 = max({a.ff.ff, a.ss.ff, b.ff.ff, b.ss.ff});
        MX2 = max({(a.ff.ff != MX1) ? a.ff.ff : 0, (a.ss.ff != MX1) ? a.ss.ff : 0, (b.ff.ff != MX1) ? b.ff.ff : 0, (b.ss.ff != MX1) ? b.ss.ff : 0});
        int cnt1 = 0, cnt2 = 0;
        if(MX1 == a.ff.ff) cnt1 += a.ff.ss;
        else if(MX2 == a.ff.ff) cnt2 += a.ff.ss;

        if(MX1 == a.ss.ff) cnt1 += a.ss.ss;
        else if(MX2 == a.ss.ff) cnt2 += a.ss.ss;

        if(MX1 == b.ff.ff) cnt1 += b.ff.ss;
        else if(MX2 == b.ff.ff) cnt2 += b.ff.ss;

        if(MX1 == b.ss.ff) cnt1 += b.ss.ss;
        else if(MX2 == b.ss.ff) cnt2 += b.ss.ss;

        return {{MX2, cnt2}, {MX1, cnt1}};
    }
    pair<pair<int, int>, pair<int, int>> get(int idx, int l, int r, int curL, int curR)
    {

        if(l == curL && r == curR)
        {
            pair<pair<int, int>, pair<int, int>> res = {{prev(prev(tree[idx].end()))->ff, prev(prev(tree[idx].end()))->ss}, {prev(tree[idx].end())->ff, prev(tree[idx].end())->ss}};
            return res;
        }

        int mid = (curL + curR) >> 1;

        if(l < mid && mid < r)
        {
            return combine(get(idx * 2 + 1, l, min(r, mid), curL, mid), get(idx * 2 + 2, max(l, mid), r, mid, curR));
        }
        else if(r <= mid)
        {
            return get(idx * 2 + 1, l, min(r, mid), curL, mid);
        }
        else
        {
            return get(idx * 2 + 2, max(l, mid), r, mid, curR);   
        }

    }
    void calc(int idx)
    {
        if(tree[idx * 2 + 1].size() < tree[idx * 2 + 2].size())
        {
            tree[idx] = tree[idx * 2 + 2];
            for(auto& [k, v] : tree[idx * 2 + 1])
            {
                tree[idx][k] += v;
            }
        }
        else
        {
            tree[idx] = tree[idx * 2 + 1];
            for(auto& [k, v] : tree[idx * 2 + 2])
            {
                tree[idx][k] += v;
            }   
        }
    }
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx][0]++;
            tree[idx][vec[l]]++;
            return;
        }
        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);
        calc(idx);
    }
};
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> vec(n);
    input(vec);
    Tree ST(vec);
    for(int i = 0; i < q; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int pos;
            ll val;
            cin >> pos >> val;
            ST.update(pos - 1, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << ST.get(l - 1, r) << endl;
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