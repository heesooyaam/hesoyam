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
#define checker cout << "!!!" << endl;
#define endl '\n'   
const ll INF = numeric_limits<ll>::max();
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
struct request
{
    int type;
    ll l, r;
};
struct Tree
{
    Tree(size_t size, const vector<ll>& idxToval, unordered_map<ll, int, custom_hash>& valToIdx)
    : n(size)
    , tree(n * 4, Node())
    , idxToVal(idxToval)
    , valToIdx(valToIdx)
    {
        build(0, 0, n);
    }
    void update(ll l, ll r, int type)
    {
        update(0, valToIdx[l], valToIdx[r + 1], 0, n, type);
    }
    ll getMEX()
    {
        return getMEX(0, 0, n);
    }
private:
    int n;
    struct Node
    {
        int act = 0; // 0 - no changings, 1 - all numbers added, 2 - all numbers deleted, 3 - reverse
        ll sum = 0;
        ll len = 0;
    };
    vector<Node> tree;
    const vector<ll>& idxToVal;
    unordered_map<ll, int, custom_hash>& valToIdx;
    void recalc(int idx)
    {
        int l_child = idx * 2 + 1, r_child = l_child + 1;
        tree[idx].sum = tree[l_child].sum + tree[r_child].sum; 
    }
    void build(int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].len = idxToVal[r] - idxToVal[l];
            tree[idx].sum = 0;
            tree[idx].act = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid);
        build(idx * 2 + 2, mid, r);
        tree[idx].len = tree[idx * 2 + 1].len + tree[idx * 2 + 2].len;
    }
    void add(int idx)
    {
        tree[idx].act = 1;
        tree[idx].sum = tree[idx].len;
    }
    void del(int idx)
    {
        tree[idx].act = 2;
        tree[idx].sum = 0;
    }
    void reverse(int idx)
    {
        if(tree[idx].act == 3) tree[idx].act = 0;
        else tree[idx].act = 3;
        tree[idx].sum = tree[idx].len - tree[idx].sum;
    }
    void push(int idx, int curL, int curR)
    {
        if(tree[idx].act == 0 || curL + 1 == curR) return;

        int l_child = idx * 2 + 1, r_child = idx * 2 + 2, mid = (curL + curR) >> 1;


        if(tree[idx].act == 3)
        {
            if(tree[l_child].act != 3) push(l_child, curL, mid);
            if(tree[r_child].act != 3) push(r_child, mid, curR);
            modifyNode(l_child, tree[idx].act);
            modifyNode(r_child, tree[idx].act);
        }
        else
        {
            modifyNode(l_child, tree[idx].act);
            modifyNode(r_child, tree[idx].act);
        }        
        tree[idx].act = 0;
    }
    void modifyNode(int idx, int type)
    {
        if(type == 1) add(idx);
        else if(type == 2) del(idx);
        else reverse(idx);
    }
    void update(int idx, int l, int r, int curL, int curR, int type)
    {
        if(l >= r) return;
        push(idx, curL, curR);
        if(l == curL && r == curR)
        {  
           modifyNode(idx, type);
           return; 
        }
        int mid = (curL + curR) / 2;
        update(idx * 2 + 1, l, min(r, mid), curL, mid, type);
        update(idx * 2 + 2, max(l, mid), r, mid, curR, type);
        recalc(idx);
    }
    ll getMEX(int idx, int l, int r)
    {
        // if(tree[idx].len == tree[idx].sum) return tree[idx].sum;

        if(l + 1 == r)
        {
            return idxToVal[l];
        }

        push(idx, l, r);

        int mid = (l + r) / 2;

        if(tree[idx * 2 + 1].len == tree[idx * 2 + 1].sum)
        {
            return getMEX(idx * 2 + 2, mid, r);
        }
        else
        {
            return getMEX(idx * 2 + 1, l, mid);
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<request> requests(n);
    set<ll> borders;
    for(int i = 0; i < n; ++i)
    {
        cin >> requests[i].type >> requests[i].l >> requests[i].r;
        borders.insert(requests[i].l);
        borders.insert(requests[i].r);
        borders.insert(requests[i].r + 1);
    }
    borders.insert(1);
    // borders.pb(2);
    vector<ll> idxToVal(borders.size());
    unordered_map<ll, int, custom_hash> valToIdx;
    int ptr = 0;
    for(const auto& x : borders)
    {
        idxToVal[ptr] = x;
        valToIdx[x] = ptr++;
    }
    // cout << borders.size() << endl;
    // print(borders);
    Tree ST(idxToVal.size(), idxToVal, valToIdx);
    for(int i = 0; i < n; ++i)
    {
        ST.update(requests[i].l, requests[i].r, requests[i].type);
        cout << ST.getMEX() << endl;
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