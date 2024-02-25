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
struct GCDTree
{
    GCDTree(const vector<ll>& vec)
    : n(vec.size())
    {
        tree.assign(n * 4, 0);
        build(0, 0, n, vec);
    }
    void update(int pos, ll val)
    {
        update(0, pos, 0, n, val);
    }
    ll getGCD(int l, int r)
    {
        return getGCD(0, l, r, 0, n);
    }
    bool isXok(int l, int r, ll x)
    {
        // if(getGCD(l, r) % x == 0) return true;
    
        return isXok(0, l, r, 0, n, x) <= 1;
    }
private:
    int n;
    vector<ll> tree;
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = vec[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        tree[idx] = gcd(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    void update(int idx, int pos, int l, int r, ll val)
    {
        if(l + 1 == r)
        {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos < mid) update(idx * 2 + 1, pos, l, mid, val);
        else update(idx * 2 + 2, pos, mid, r, val);
        tree[idx] = gcd(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
    ll getGCD(int idx, int l, int r, int curL, int curR)
    {
        // cout << l << " " << r << endl;
        // assert(l < r);
        if(curL == l && curR == r)
        {
            return tree[idx];
        }

        int mid = (curL + curR) / 2;
        ll lGCD = -1, rGCD = -1;
        if(l < mid) lGCD = getGCD(idx * 2 + 1, l, mid, curL, mid);
        if(mid < r) rGCD = getGCD(idx * 2 + 2, mid, r, mid, curR);
        if(lGCD == -1) return rGCD;
        if(rGCD == -1) return lGCD;
        return gcd(lGCD, rGCD);
    }
    int isXok(int idx, int l, int r, int curL, int curR, ll x)
    {
        if(l >= r) return 0;
        if(curL + 1 == curR)
        {
            if((tree[idx] % x) == 0) return 0;
            return 1;
        }
        if(l == curL && r == curR)
        {
            if(tree[idx] % x == 0) return 0;
            if((tree[idx * 2 + 1] % x) != 0 && (tree[idx * 2 + 2] % x) != 0) return 2;
            int mid = (curL + curR) / 2;
            if((tree[idx * 2 + 1] % x) != 0) return isXok(idx * 2 + 1, l, mid, curL, mid, x);
            if((tree[idx * 2 + 2] % x) != 0) return isXok(idx * 2 + 2, mid, r, mid, curR, x);
        }
        int mid = (curL + curR) / 2;
        ll resL = isXok(idx * 2 + 1, l, min(r, mid), curL, mid, x);
        ll resR = 0;
        if(resL <= 1) resR = isXok(idx * 2 + 2, max(l, mid), r, mid, curR, x);
        return resR + resL; 
    }
};
void solve()
{
    int n;
    cin >> n;
    vector<ll> vec(n);
    input(vec);
    GCDTree ST(vec);
    int m;
    cin >> m;
    // cout << ST.getGCD(1, 4) << endl;
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            --l;
            // cout << ST.getGCD(l, r) << endl;
            if(ST.isXok(l, r, x)) cout << "YES\n";
            else cout << "NO\n";
        }
        else
        {
            int pos;
            ll val;
            cin >> pos >> val;
            --pos;
            ST.update(pos, val);
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