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

struct InversionsTree
{
    InversionsTree(size_t size)
    {
        n = size;
        tree.resize(n * 4);
    }
    InversionsTree(const vector<int>& vec)
    {
        n = vec.size();
        tree.resize(n * 4);
        build(vec);
    }
    void build(const vector<int>& vec)
    {
        build(0, 0, n, vec);
    }
    int countInversions(int l, int r)
    {
        return countInversions(0, l, r, 0, n).inversions;
    }
    void update(int pos, int val)
    {
        update(pos, val, 0, 0, n);
    }
private:
    struct Node
    {
        map<int, int> cnt;
        int inversions = 0;
    };
    int n;
    vector<Node> tree;
    Node merge(const Node a, const Node b) const
    {
        Node ab;
        auto itA = a.cnt.begin(), itB = b.cnt.begin();
        int pref = 0;
        // string log = "start ";
        while(itA != a.cnt.end() || itB != b.cnt.end())
        {
            while(itA != a.cnt.end() && itB != b.cnt.end())
            {
                while(itA != a.cnt.end() && itB != b.cnt.end() && itA->ff <= itB->ff)
                {
                    // log += "-> 1 ";
                    ab.cnt[itA->ff] += itA->ss;
                    ++itA;
                }
                while(itA != a.cnt.end() && itB != b.cnt.end() && itA->ff > itB->ff)
                {
                    // log += "-> 2 ";
                    pref += itB->ss;
                    ab.cnt[itB->ff] += itB->ss;
                    ++itB;
                    if(itB == b.cnt.end() || itA->ff <= itB->ff)
                    {
                        if(itB == b.cnt.end()) continue;
                        ab.inversions += pref;
                    }
                }
            }
            if(itA == a.cnt.end())
            {
                for(; itB != b.cnt.end(); ++itB)
                {
                    // log += "-> 3 ";
                    ab.cnt[itB->ff] += itB->ss;
                }
            }
            else if(itB == b.cnt.end())
            {
                for(; itA != a.cnt.end(); ++itA)
                {
                    // log += "-> 4 ";
                    ab.cnt[itA->ff] += itA->ss;
                    ab.inversions += pref;
                }
            }
        }
        ab.inversions += a.inversions + b.inversions;
        // cout << "logged: " << log << endl;
        return ab;
    }
    void build(int idx, int l, int r, const vector<int>& vec)
    {
        if(l + 1 == r)
        {
            ++tree[idx].cnt[vec[l]];
            return;
        }

        int mid = (l + r) / 2;
        
        build(idx * 2 + 1, l, mid, vec);
        build(idx * 2 + 2, mid, r, vec);

        tree[idx] = merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }

    Node countInversions(int idx, int l, int r, int curL, int curR)
    {
        if(l >= r)
        {
            return Node();
        }

        if(l == curL && r == curR)
        {
            return tree[idx];
        }

        int mid = (curL + curR) / 2;

        return merge(countInversions(idx * 2 + 1, l, min(r, mid), curL, mid), countInversions(idx * 2 + 2, max(l, mid), r, mid, curR));

    }

    void update(int pos, int val, int idx, int l, int r)
    {
        if(l + 1 == r)
        {
            tree[idx].cnt.clear();
            ++tree[idx].cnt[val];
            return;
        }

        int mid = (l + r) / 2;

        if(pos < mid)
        {
            update(pos, val, idx * 2 + 1, l, mid);
        }
        else
        {
            update(pos, val, idx * 2 + 2, mid, r);
        }

        tree[idx] = merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> vec(n);
    input(vec);
    InversionsTree ST(vec);

    // Node a;
    // a.cnt = {{2, 1}, {4, 1}, {6, 1}};
    // a.inversions = 0;
    // Node b;
    // b.cnt = {{1, 1}, {2, 1}, {4, 1}};
    // b.inversions = 0;
    // Node res = merge(a, b);
    // cout << res.inversions << endl;
    // for(auto& [x, amt] : res.cnt)
    // {
    //     cout << "amount of " << x << " = " << amt << endl;
    // }
    for(int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << ST.countInversions(l - 1, r) << endl;
        }
        else
        {
            int pos, val;
            cin >> pos >> val;
            ST.update(pos - 1, val);
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