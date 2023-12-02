#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
struct SegTree
{
    struct Node
    {
        ll sum = 0;
    };
    SegTree(vector<int>& vec)
    {
        this->n = vec.size();
        t.assign(n << 2, {});
        build(vec);
    }
    void build(const vector<int>& vec)
    {
        build(0, 0, vec.size(), vec);
    }
    ll getSum(int l, int r) 
    {
        if(l >= r) return 0;
        
        return (getSum(0, l, r, 0, n)).sum;
    }
    void update(int pos, ll val)
    {
        update(pos, val, 0, 0, n);
    }
private:
    int n;
    vector<Node> t;
    void build(int ind, int l, int r, const vector<int>& vec)
    {
        if(l + 1 == r)
        {
            t[ind] = {.sum = vec[l]};
            return; 
        }
        int mid = (l + r) >> 1;
        build((ind << 1) + 1, l, mid, vec);
        build((ind << 1) + 2, mid, r, vec);
        t[ind] = combine(t[(ind << 1) + 1], t[(ind << 1) + 2]);
    }
    Node getSum(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r) return {.sum = 0};
        if(l == curL && r == curR) return t[idx];
        int mid = (curL + curR) >> 1;
        return combine(getSum((idx << 1) + 1, l, min(r, mid), curL, mid),
        getSum((idx << 1) + 2, max(l, mid), r, mid, curR));
    }
    void update(int pos, int val, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            t[idx].sum = val;
            return;
        }

        int mid = (l + r) >> 1;

        if(pos < mid) update(pos, val, (idx << 1) + 1, l, mid);
        else update(pos, val, (idx << 1) + 2, mid, r);

        t[idx] = combine(t[(idx << 1) + 1], t[(idx << 1) + 2]);
    }
    Node combine(const Node& a, const Node& b) const
    {
        return {.sum = (a.sum + b.sum)};
    }
};
void solve(ifstream& in, ofstream& out)
{
    int n, k;
    in >> n >> k;
    vector<int> vec(n, 0);
    SegTree ST(vec);
    
    while(k--)
    {
        char r;
        int x, y;
        in >> r >> x >> y;
        if(r == 'A')
        {
            ST.update(x - 1, y);
        }
        else
        {
            out << ST.getSum(x - 1, y) << endl;
        }
    }
}
int main()
{
    ifstream in("sum.in");
    ofstream out("sum.out");
    // freopen("sum.in", "r", stdin);
    // freopen("sum.out", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve(in, out);
    return 0;
}