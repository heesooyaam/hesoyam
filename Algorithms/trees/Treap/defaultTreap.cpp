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
    void insert(T key)
    {
        
        if(Root == -1)
        {
            ++size_;
            Root = AllocateNode(key);
            return;
        }

        if(contains(key)) return;

        insert(Root, key);
    }
    void erase(T key)
    {
        erase(Root, key);
    }
    bool contains(T val)
    {
        if(find(Root, val) != -1) return true;
        else return false;
    }
    T lower_bound(T val)
    {
        return lower_bound(Root, val);
    }
    size_t size() const
    {
        return size_;
    }
private:
    struct Node
    {
        T key;
        int priority;
        int l_child, r_child;
        Node(T key, int priority)
        : key(key)
        , priority(priority)
        , l_child(-1)
        , r_child(-1)
        {}
    };
    int Root;
    size_t size_;
    vector<Node> tree;
    int AllocateNode(T key)
    {
        tree.eb(key, GeneratePriority());
        return tree.size() - 1;
    }
    int merge(int l_node, int r_node)
    {
        if(l_node == -1) return r_node;
        if(r_node == -1) return l_node;

        if(tree[l_node].priority < tree[r_node].priority)
        {
            tree[r_node].l_child = merge(l_node, tree[r_node].l_child);
            return r_node;
        }
        else
        {
            tree[l_node].r_child = merge(tree[l_node].r_child, r_node);
            return l_node;
        }
    }
    pair<int, int> split(int root, T key) // если есть нода с ключом key, то она окажется первой в правом поддереве
    {
        if(root == -1) return {-1, -1};

        if(tree[root].key < key)
        {
            auto res = split(tree[root].r_child, key);
            tree[root].r_child = res.ff;
            return {root, res.ss};
        }
        else
        {
            auto res = split(tree[root].l_child, key);
            tree[root].l_child = res.ss;
            return {res.ff, root};
        }
    }
    int GeneratePriority()
    {
        static int mn = -1e9;
        static int mx = 1e9;
        static mt19937 Generator(42);
        return uniform_int_distribution<int>(mn, mx)(Generator);
    }
    void insert(int root, T key)
    {
        auto [l_child, r_child] = split(root, key);
        auto [x, rr_child] = split(r_child, key + 1);
        if(x != -1)
        {
            Root = merge(l_child, merge(x, rr_child));
        }
        else
        {
            ++size_;
            int newNode = AllocateNode(key);
            Root = merge(l_child, merge(newNode, rr_child));
        }
    }
    int find(int root, T key)
    {
        if(root == -1) return -1;

        if(tree[root].key == key) return root;

        if(tree[root].key < key) return find(tree[root].r_child, key);
        else return find(tree[root].l_child, key);
    }
    void erase(int root, T key)
    {
        auto [l_child, r_child] = split(root, key);
        auto [x, rr_child] = split(r_child, key + 1);
        if(x != -1) --size_;
        Root = merge(l_child, rr_child);
    }
    T lower_bound(int root, T key)
    {
        int curRoot = root;
        int curIt = -1;
        while(curRoot != -1)
        {
            if(tree[curRoot].key >= key)
            {
                curIt = curRoot;
                curRoot = tree[curRoot].l_child;
            }
            else
            {
                curRoot = tree[curRoot].r_child;
            }
        }
        return (curIt == -1) ? -1 : tree[curIt].key;
    }
};

void solve()
{
    int n;
    cin >> n;
    Treap<int> T;
    // set<int> st;
    char prev = '+';
    int result = 0;
    ll MOD = 1'000'000'000;
    // vector<int> checker(10), askQ(10);
    // for(int i = 0; i < 10; ++i)
    // {
    //     checker[i] = i;
    // }
    // askQ = checker;
    // random_shuffle(all(askQ));
    // random_shuffle(all(checker));
    

    for(int i = 0; i < n; ++i)
    {
        char ch;
        int val;
        // if(i % 2 == 0)
        // {
        //     ch = '+';
        //     val = checker[i / 2];
        // }
        // else
        // {
        //     ch = '?';
        //     val = askQ[i / 2];
        // }
        cin >> ch >> val;
        if(ch == '+')
        {
            // cerr << "inserted ";
            if(prev == ch)
            {
                // st.insert(val);
                T.insert(val);
                // cerr << val << endl;
            }
            else
            {
                // st.insert((val + result + MOD) % MOD);
                T.insert((val + result + MOD) % MOD);
                // cerr << (val + result + MOD) % MOD << endl;
            }
        }
        else
        {
            // int help = (st.lower_bound(val) != st.end()) ? *st.lower_bound(val) : -1;
            result = T.lower_bound(val);
            // cerr << "were looking for " << val << ", found " << result << '/' << help << endl;
            // assert(help == result);
            cout << result << endl;
        }
        prev = ch;
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