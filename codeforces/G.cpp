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

struct SumTree
{
private:
    int n;
    ll def;
    vector<ll> tree;
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx] = def;
            return; 
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);

        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = vec[l];
            return; 
        }

        int mid = (l + r) / 2;

        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
    }
};

void solve()
{
    
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1; 
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}