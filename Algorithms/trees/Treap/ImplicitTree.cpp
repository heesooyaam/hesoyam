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

template<typename T>
class Treap
{
public:
    Treap()
    : Root(-1)
    , size_(0)
    {}
    void insert(int pos, T val)
    {
        
        if(Root == -1)
        {
            Root = AllocateNode(val);
            return;
        }

        insert(Root, pos, val);
    }
    void push_back(T val)
    {
        int newNode = AllocateNode(val);
        Root = merge(Root, newNode);
    }
    void erase(ll key)
    {
        erase(Root, key);
    }
    size_t size() const
    {
        return size_;
    }
    void moveToFront(int l, int r)
    {
        if(l == 0) return;
        moveToFront_(l, r);
    }
    T get(int idx)
    {
        return get(Root, idx);
    }
    void shandom_ruffle(int a, int b)
    {
        if(a >= b) return;
        int l1, l2, r1, r2;
        l1 = a;
        l2 = b;
        r1 = l1 + min((int) size() - b, b - a);
        r2 = l2 + min((int) size() - b, b - a);
        // cout << l1 << ' ' << r1 << ", " << l2 << ' ' << r2 << endl;
        swap(l1, r1, l2, r2);
    }
private:
    struct Node
    {
        ll key;
        T value;
        int priority;
        int l_child, r_child;
        Node(int priority, T value)
        : key(1)
        , value(value)
        , priority(priority)
        , l_child(-1)
        , r_child(-1)
        {}
    };
    int Root;
    size_t size_;
    vector<Node> tree;
    // helpful functions
    int AllocateNode(T val)
    {
        ++size_;
        tree.eb(GeneratePriority(), val);
        return tree.size() - 1;
    }
    int GeneratePriority()
    {
        static int mn = -1e9;
        static int mx = 1e9;
        static mt19937 Generator(42);
        return uniform_int_distribution<int>(mn, mx)(Generator);
    }
    int getKey(int root)
    {
        return ((root == -1) ? 0 : tree[root].key);
    }
    void recalc(int root)
    {
        tree[root].key = 1 + getKey(tree[root].l_child) + getKey(tree[root].r_child);
    }

    // split && merge
    int merge(int l_node, int r_node)
    {
        if(l_node == -1) return r_node;
        if(r_node == -1) return l_node;

        if(tree[l_node].priority < tree[r_node].priority)
        {
            tree[r_node].l_child = merge(l_node, tree[r_node].l_child);
            recalc(r_node);
            return r_node;
        }
        else
        {
            tree[l_node].r_child = merge(tree[l_node].r_child, r_node);
            recalc(l_node);
            return l_node;
        }
    }
    pair<int, int> split(int root, ll key) // если есть нода с ключом key, то она окажется первой в правом поддереве
    {
        if(root == -1) return {-1, -1};

        int curKey = getKey(tree[root].l_child);

        if(curKey < key)
        {
            auto [lr_child, rr_child] = split(tree[root].r_child, key - curKey - 1);
            tree[root].r_child = lr_child;
            recalc(root);
            return {root, rr_child};
        }
        else
        {
            auto [ll_child, rl_child] = split(tree[root].l_child, key);
            tree[root].l_child = rl_child;
            recalc(root);
            return {ll_child, root};
        }
    }

    // another functions

    void insert(int root, int key, T value) // insert after elemnt with idx = key, element value
    {
        auto [l_child, r_child] = split(root, key + 1);
    
        ++size_;
        int newNode = AllocateNode(value);
        Root = merge(l_child, merge(newNode, r_child));
    }
    
    T get(int root, int key) // get elemnt with idx = key
    {
        if(root == -1) return -1;

        int curKey = getKey(tree[root].l_child);

        if(curKey == key) return tree[root].value;

        if(curKey < key) return get(tree[root].r_child, key - (curKey + 1));
        else return get(tree[root].l_child, key);
    }
    void erase(int root, ll key) // erase elemnt with idx = key
    {
        auto [l_child, r_child] = split(root, key);
        auto [x, rr_child] = split(r_child, key + 1);
        if(x != -1) --size_;
        Root = merge(l_child, rr_child);
    }

    void moveToFront_(int l, int r) // move to front segment [l, r)
    {
        auto [midL_node, r_node] = split(Root, r);
        auto [l_node, middle] = split(midL_node, l);

        Root = merge(merge(middle, l_node), r_node);
    }

    void swap(int l1, int r1, int l2, int r2) // ...[l1, r1)...[l2, r2)... --> ...[l2, r2)...[l1, r1)... 
    {
        auto [lr2_node, r2_node] = split(Root, r2);
        auto [ll2_node, seg2] = split(lr2_node, l2);
        auto [lr1_node, r1_node] = split(ll2_node, r1);
        auto [ll1_node, seg1] = split(lr1_node, l1);
        // [ll1_node], [seg1], [r1_node], [seg2], [r2_node]
        Root = merge(ll1_node, merge(seg2, merge(r1_node, merge(seg1, r2_node))));
    }
};

void solve()
{
    int n;
    cin >> n;
    Treap<int> T;
    for(int i = 1; i < n + 1; ++i)
    {
        T.push_back(i);
    }
    for(int i = 0; i < n; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a; --b;
        T.shandom_ruffle(a, b);
    }
    for(int i = 0; i < n; ++i)
    {
        cout << T.get(i) << ' ';
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