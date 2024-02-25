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
// #define endl '\n'   

struct Tree
{
    Tree(vector<int>& itx, unordered_map<int, int>& xti)
    : n(itx.size())
    , idxToX(itx)
    , xToIdx(xti)
    {
        tree.assign(n * 4, {});
        cerr << "!!builded!!" << endl;
    }

    void add(int x, int y)
    {
        add(0, 0, n, xToIdx[x], y);
        // cout << xToIdx[x]<< ' ' << y << " added" << endl;
    }
    void remove(int x, int y)
    {
        remove(0, 0, n, xToIdx[x], y);
    }
    pair<int, int> find(int x, int y)
    {
        auto res = find(0, 0, n, xToIdx[x], y);
        if(res == mp(-1, -1)) return res;
        else return mp(idxToX[res.ff], res.ss);
    }
private:
    int n;
    vector<multiset<pair<int, int>>> tree;
    vector<int>& idxToX;
    unordered_map<int, int>& xToIdx;

    void add(int idx, int l, int r, int x, int y)
    {
        if(l + 1 == r)
        {
            tree[idx].insert({x, y});
            // cout << "list" << endl;
            return;
        }

        int mid = (l + r) / 2;
        // cout << l << " " << r << " " << mid << endl;

        if(x < mid) add(idx * 2 + 1, l, mid, x, y);
        else add(idx * 2 + 2, mid, r, x, y);

        tree[idx].insert(mp(x, y));
    }
    void remove(int idx, int l, int r, int x, int y)
    {
        if(l + 1 == r)
        {
            tree[idx].erase(mp(x, y));
            return;
        }

        int mid = (l + r) / 2;

        if(x < mid) remove(idx * 2 + 1, l, mid, x, y);
        else remove(idx * 2 + 2, mid, r, x, y);
        tree[idx].erase(tree[idx].find(mp(x, y)));
    }

    pair<int, int> find(int idx, int l, int r, int x, int y)
    {
        if(r <= x || x >= n) return mp(-1, -1);
        if(l >= x)
        {
            auto it = tree[idx].upper_bound(mp(x, y));
            if(it == tree[idx].end())
            {
                return mp(-1, -1);
            }
            else return *it;
        }

        int mid = (l + r) / 2;
        
        auto ans = find(idx * 2 + 1, l, mid, x, y);

        return (ans != mp(-1, -1)) ? ans : find(idx * 2 + 2, mid, r, x, y);
    }
    
};
struct request
{
    int type, x, y;
    // type = 1 - add, type = 2 - remove, type = 3 - find
};
void solve()
{
    int n;
    cin >> n;
    vector<request> requests(n);
    set<int> borders;
    for(int i = 0; i < n; ++i)
    {
        string action;
        cin >> action;
        if(action[0] == 'a') requests[i].type = 1;
        else if(action[0] == 'r') requests[i].type = 2;
        else requests[i].type = 3;
        cin >> requests[i].x >> requests[i].y;
        borders.insert(requests[i].x);
    }
    vector<int> idxToVal(borders.size());
    unordered_map<int, int> valToIdx;
    int ptr = 0;
    for(auto& x : borders)
    {
        idxToVal[ptr] = x;
        valToIdx[x] = ptr++;
    } 
    Tree ST(idxToVal, valToIdx);
    int i = 0;
    for(auto& [rec, x, y] : requests)
    {
        cerr << ++i << " query\n";

        if(rec == 1) ST.add(x, y);
        else if(rec == 2) ST.remove(x, y);
        else
        {
            auto res = ST.find(x, y);
            cout << res.ff << ' ' << res.ss << endl;
        }
        // cout << "ended" << endl;
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