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
        if(l >= r) return;
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
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    input(a);
    vector<int> b(m);
    input(b);
    SumAddTree<ll> ST(a);
    for(int i = 0; i < m; ++i)
    {
        int box = b[i];

        // cout << "step No" << i + 1 << ", box = " << box << ", amount of balls"

        ll cnt = ST.getSum(box, box + 1);
        
        ST.update(box, box + 1, -cnt);

        ll k = cnt / n;

        ll ost = cnt % n;

        ST.update(0, n, k);

        if(ost)
        {
            if(box == n - 1)
            {
                int l = 0, r = ost;
                ST.update(l, r, 1);
            }
            else
            {
                int l1 = box + 1;
                int r1 = ((box + ost) < n) ? box + ost + 1 : n;
                int l2 = 0;
                int r2 = ((box + ost) < n) ? 0 : (box + ost) % n + 1;
                ST.update(l1, r1, 1);
                ST.update(l2, r2, 1);

            }
        }
    }

    for(int i = 0; i < n; ++i)
    {
        cout << ST.getSum(i, i + 1) << ' ';
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