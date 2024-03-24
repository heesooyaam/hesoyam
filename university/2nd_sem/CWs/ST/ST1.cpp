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

int main()
{
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    input(vec);
    Tree ST(vec);
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << ST.getSum(l - 1, r) << endl;
        }
        else
        {
            int l, r;
            ll a, b, c;
            cin >> l >> r >> a >> b >> c;
            ST.update(l - 1, r, a + l * b, a + b, c);
        }
    }
}