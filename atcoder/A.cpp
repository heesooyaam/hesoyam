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
    SumAddTree(const vector<T>& vec)
            : n(vec.size())
    {
        tree.assign(n * 4, Node());
        build(0, 0, n, vec);
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
    void build(int idx, int l, int r, const vector<T>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx].sum = vec[l];
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

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
    vector<ll> vec(n);
    input(vec);
    sort(all(vec));
    SumAddTree<ll> ST(vec.back() + 1);
    ST.update(vec.front(), vec.front() + 1, 1);
    ll ans = 0;

    for(int i = 1; i < n; ++i)
    {
        ll d = 1;
        ll cur = vec[i] / d;
        ll l = 1, r = vec[i] / cur;
        while(cur <= vec[i] && cur > 0 && l <= r && r < vec[i])
        {
            ans += cur * ST.getSum(l, r + 1);
            ++d;
            if(cur == vec[i] / d || vec[i] / d <= 0) break;
            cur = vec[i] / d;
            if(!(cur <= vec[i] && cur > 0 && l <= r && r < vec[i])) break;
            l = max((vec[i] - cur) / cur + !bool(vec[i] % cur), 1ll);
            r = vec[i] / cur;
        }
        ST.update(vec[i], vec[i] + 1, 1);
    }
    cout << ans << endl;
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