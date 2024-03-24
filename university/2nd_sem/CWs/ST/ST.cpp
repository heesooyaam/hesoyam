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
// #define endl '\n'   
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
    ll a, b, c;
};
struct Tree
{
    Tree(const vector<ll>& vec)
    : n(vec.size())
    , tree(n * 4, Node())
    {
        build(0, 0, n, vec);
    }
    void update(int l, int r, ll a, ll d, ll c)
    {
        updateProg(0, l, r, 0, n, a, d);
        updateConst(0, l, r, 0, n, c);
    }
    ll getSum(int l, int r)
    {
        return getSum(0, l, r, 0, n);
    }
private:
    int n;
    struct Node
    {
        bool push = false;
        ll a1 = 0;
        ll d = 0;
        ll add = 0;
        ll sum = 0;
    };
    vector<Node> tree;
    
    void recalc(int idx)
    {
        int l_child = idx * 2 + 1, r_child = l_child + 1;
        tree[idx].sum = tree[l_child].sum + tree[r_child].sum; 
    }
    void build(int idx, int l, int r, const vector<ll>& vec)
    {
        if(l + 1 == r)
        {
            tree[idx] = {false, 0, 0, 0, vec[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);
        recalc(idx);
    }
    
    void push(int idx, int curL, int curR)
    { 
        if(tree[idx].push == false || curL + 1 == curR) return;

        int l_child = idx * 2 + 1, r_child = l_child + 1;
        int mid = (curL + curR) / 2;

        ll d = tree[idx].d; 

        int len_l = mid - curL;
        ll a1_l = tree[idx].a1;

        tree[l_child].a1 += tree[idx].a1;
        tree[l_child].d += d;
        tree[l_child].add += tree[idx].add;
        tree[l_child].sum += (2 * a1_l + d * (len_l - 1)) * (len_l) / 2 + tree[idx].add * len_l; 
        tree[l_child].push = true;
        

        int len_r = curR - mid;
        ll a1_r = a1_l + d * (len_l);

        tree[r_child].a1 += a1_r;
        tree[r_child].d += d;
        tree[r_child].add += tree[idx].add;
        tree[r_child].sum += (2 * a1_r + d * (len_r - 1)) * (len_r) / 2 + tree[idx].add * len_r;
        tree[r_child].push = true;

        tree[idx].a1 = 0;
        tree[idx].d = 0;
        tree[idx].add = 0;
        tree[idx].push = false;
    }
    
    void updateProg(int idx, int l, int r, int curL, int curR, ll a, ll d)
    {
        if(curL >= r || curR <= l) return;
        push(idx, curL, curR);
        // cout << curL << ' ' << curR << endl;
        if(l <= curL && r <= curR)
        {  
           ll realA = a + d * (curL - l);
           tree[idx].a1 += realA;
           tree[idx].d += d;
           int len = curR - curL;
           tree[idx].sum += (2 * realA + d * (len - 1)) * (len) / 2;
           tree[idx].push = true;
           return; 
        }
        int mid = (curL + curR) / 2;
        updateProg(idx * 2 + 1, l, r, curL, mid, a, d);
        updateProg(idx * 2 + 2, l, r, mid, curR, a, d);
        recalc(idx);
    }
    void updateConst(int idx, int l, int r, int curL, int curR, ll c)
    {
        if(l >= r) return;
        push(idx, curL, curR);
        if(l == curL && r == curR)
        {
            tree[idx].add += c;
            tree[idx].sum += c * (curR - curL);
            tree[idx].push = true;
            return;
        }
        int mid = (curR + curL) / 2;
        updateConst(idx * 2 + 1, l, min(r, mid), curL, mid, c);
        updateConst(idx * 2 + 2, max(l, mid), r, mid, curR, c);
        recalc(idx);
    }
    ll getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return 0;

        push(idx, curL, curR);

        if(curL == l && curR == r)
        {
            return tree[idx].sum;
        }

        int mid = (curL + curR) / 2;

        return getSum(idx * 2 + 1, l, min(mid, r), curL, mid) + getSum(idx * 2 + 2, max(l, mid), r, mid, curR);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    
    vector<ll> vec(n);
    Tree ST(vec);
    input(vec);
    auto countSum = [&vec](int l, int r)
    {
        ll sum = 0;
        for(int i = l; i < r; ++i)
        {
            sum += vec[i];
        }
        return sum;
    };
    vector<request> upd(m / 2);
    vector<request> ask(m - m / 2);
    static mt19937 Generator(42);
    uniform_int_distribution<int>(1, n + 1)(Generator);
    for(auto& req : upd)
    {
        req.type = 1;
        req.l = min(uniform_int_distribution<int>(1, n + 1)(Generator), n);
        req.r = min(uniform_int_distribution<int>(1, n + 1)(Generator), n);
        if(req.l > req.r) swap(req.l, req.r);
    }
    for(auto& req : ask)
    {
        req.type = 2;
        req.l = min(uniform_int_distribution<int>(1, n + 1)(Generator), n);
        req.r = min(uniform_int_distribution<int>(1, n + 1)(Generator), n);
        if(req.l > req.r) swap(req.l, req.r);
        req.a = uniform_int_distribution<ll>(1, 10)(Generator);
        req.b = uniform_int_distribution<ll>(1, 10)(Generator);
        req.c = uniform_int_distribution<ll>(1, 10)(Generator);
    }

    for(int i = 0; i < m; ++i)
    {
        request req;
        if(i % 2 == 0)
        {
            req = upd[i / 2];
        }
        else req = ask[i / 2];
        if(req.type == 1)
        {
            int l = req.l;
            int r = req.r;
            ll truth = countSum(l - 1, r);
            ll counted = ST.getSum(l - 1, r);
            cout << "sum on segment ["<< l << ", " << r << "]; real sum = " << truth << ", counted in SegTree sum = ";
            cout << counted << endl;
            assert(counted == truth);
        }
        else
        {
            int l = req.l;
            int r = req.r;
            ll a = req.a, b = req.b, c = req.c;
            cout << "updated segment ["<< l << ", " << r << "] with " <<  "a = " << a << ", b = " << b << ", c = " << c << endl;
            for(int i = l - 1; i < r; ++i)
            {
                vec[i] += a * (i - l + 2) + b * (i + 1) + c;
            }
            ST.update(l - 1, r, a + l * b, a + b, c);
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