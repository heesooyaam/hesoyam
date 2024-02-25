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


class Treap
{
private:
    struct Node
    {
        int key;
        int priority;
        int l_child = -1;
        int r_child = -1;
    };
    int AllocateNode()
    {
        tree.eb();
        return tree.size() - 1;
    }
    vector<Node> tree;
    int Merge(int left, int right)
    {
        if(left == -1) return right;
        if(right == - 1) return left;

        if(tree[left].priority >= tree[right].priority)
        {
            tree[left].r_child = Merge(tree[left].r_child, right);
            return left;
        }
        else
        {
            tree[right].l_child = Merge(left, tree[right].l_child);
            return left;
        }
    }
    pair<int, int> Split(int root, int key)
    {
        if(root == -1)
        {
            return mp(-1, -1);
        }
        if(tree[root].key < key)
        {
            auto [RL, RR] = Split(tree[root].r_child, key);
            tree[root].r_child = RL;
            return mp(root, RR);
        }
        else
        {
            auto [LL, LR] = Split(tree[root].l_child, key);
            tree[root].l_child = LR;
            return mp(LL, root);
        }
    }
    int GeneratePriority()
    {
        static int mn = -1e9;
        static int mx = 1e9;
        static mt19937 Generator(42);
        return uniform_int_distribution<int>(mn, mx)(Generator);
    }
    int Insert(int root, int key)
    {
        auto [LSON, RSON] = Split(root, key);
        auto [RL, RR] = Split(RSON, key + 1);

        int node = AllocateNode();
        tree[node].key = key;
        tree[node].priority = GeneratePriority();

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
    // cin >> ttest;
    while(ttest--) solve();
    return 0;
}