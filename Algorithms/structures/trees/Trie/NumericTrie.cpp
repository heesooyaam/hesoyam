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
//#define endl '\n'

template<class T = int32_t>
class X_fast_Trie
{
private:
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
    using ui = uint32_t;
    using ii = int32_t;
    using iter = list<T>::iterator;

    /*
     *  trie can store numbers, which are less than 2 ^ max_power,
     *  bit indexation: elder bit has index 0
     */
    const ui max_power;
    size_t size;
    struct vertex {
        vertex() = default;
        vertex(bool bit, ii parent)
        : bit(bit)
        , parent(parent) {}

        bool bit, alieve = true;
        ii parent;
        array<ii, 2> child = {-1, -1};
        T mn = numeric_limits<T>::max(), mx = numeric_limits<T>::min();
    };
    vector<vertex> tree;
    list<T> numbers;
    vector<unordered_map<T, int>> prefixes;
    unordered_map<T, iter> place_of;
public:

    explicit X_fast_Trie(const ui max_power = sizeof(T))
    : max_power(max_power)
    , size(0)
    , prefixes(max_power + 1)
    {
        add_root();
    }

    /*
     *  returns 'true' if element was successfully inserted, 'false' if it was already in trie
     */
    bool insert(T x)
    {
        if (contains(x)) return false;

        ui tree_idx = 0;
        if(!(first_not_lower(x) == numbers.end() || *first_not_lower(x) >= x))
        {
            cout << "x: " << x << ", first_not_lower: " << *first_not_lower(x) << endl;
        }
        assert(first_not_lower(x) == numbers.end() || *first_not_lower(x) >= x);
        place_of[x] = numbers.insert(first_not_lower(x), x);
        assert(tree[tree_idx].alieve);
        recalc(tree_idx, x);

        for (ui idx = 0; idx < max_power; ++idx) {
            bool bit = get_bit(x, idx);
            ii child = tree[tree_idx].child[bit];
            if (child == -1) {
                child = add_vertex(x, bit, tree_idx, idx + 1);
            }
            else
            {
                recalc(child, x, idx + 1);
            }
            tree_idx = child;
        }
        ++size;
        return true;
    }

    /*
     *  returns 'true' if element was successfully deleted, 'false' if there was no such element
     */
    bool erase(T x) {
        if (!contains(x)) return false;

        ui length = max_power;
        ii tree_idx = prefixes[max_power][x];

        while(tree_idx != 0 && !(is_child_alive(tree_idx, 0) || is_child_alive(tree_idx, 1)))
        {
            tree_idx = delete_vertex(tree_idx, get_prefix(x, length), length);
            --length;
        }
        while(tree_idx != -1)
        {
            tree_idx = update_vertex(tree_idx);
        }

        auto to_delete = place_of.find(x);
        numbers.erase(to_delete->ss);
        place_of.erase(to_delete);
        --size;
        return true;
    }

    /*
     *  check if 'x' is in set of numbers
     */
    bool contains(T x) const {
        return place_of.contains(x);
    }

    /*
     *  returns value of first element, which is not less than 'x', else returns (T) -1
     */
    T lower_bound(T x) {
        if (contains(x)) return x;

        iter it = first_not_lower(x);
        if(it == numbers.end()) return -1;
        else return *it;
    }

private:
    /*
     *  makes root (constructor help function)
     */
    void add_root()
    {
        assert(tree.empty());
        tree.emplace_back(0, -1);
        prefixes[0][0] = 0;
    }

    /*
     *  updates 'alieve' && recalculates 'mn' && 'mx'
     */
    void recalc(ui tree_idx, T new_element, ui length = 0) {

        tree[tree_idx].mn = min(get_min(tree_idx), new_element);
        tree[tree_idx].mx = max(get_max(tree_idx), new_element);

        if(tree[tree_idx].alieve) return;
        tree[tree_idx].alieve = true;
        prefixes[length][get_prefix(new_element, length)] = tree_idx;
    }

    /*
     *  returns idx of vertex, where ends largest prefix size
     */
    ui largest_prefix(T x) {
        ui l = 0, r = max_power;

        while (l + 1 < r) {
            ui len = (l + r) >> 1;
            T prefix = x >> (max_power - len);

            auto contains = prefixes[len].find(prefix);
            if (contains == prefixes[len].end()) {
                r = len - 1;
            } else {
                l = len;
            }
        }
        auto contains = prefixes[r].find(x >> (max_power - r));
        if (contains == prefixes[r].end()) {
            return prefixes[l][x >> (max_power - l)];
        } else {
            return contains->ss;
        }
    }

    /*
     *  reutrns list iter on first greater or first smaller than 'x' element
     */
    iter succ_or_pred(T x) {
        if (size == 0) return numbers.end();

        ui idx = largest_prefix(x);
        if(is_child_alive(idx, 0))
        {
            return place_of[tree[idx].mx];
        }
        else if(is_child_alive(idx, 1))
        {
            return place_of[tree[idx].mn];
        }
        assert(false);
    }

    /*
     *  reutrns list_iter on first not upper than 'x' element
     */
    iter first_not_upper(T x) {
        if (size == 0) return numbers.end();

        auto it = succ_or_pred(x);

        if (*it > x) return --it;
        else return it;
    }

    /*
     *  returns list_iter on first not lower than 'x' element
     */
    iter first_not_lower(T x)
    {
        if (size == 0) return numbers.end();

        iter it = succ_or_pred(x);

        if (*it < x) return ++it;
        else return it;
    }

    /*
     *  reuturns true if 'bit' child of vertex 'idx' is alieve, else - false
     */
    bool is_child_alive(ui idx, bool bit) const {
        return (tree[idx].child[bit] == -1) ? false : tree[tree[idx].child[bit]].alieve;
    }

    bool are_both_childs_alive(ui tree_idx)
    {
        bool ok = true;
        for(bool&& bit : {0, 1})
        {
            ok = ok && is_child_alive(tree_idx, bit);
        }
        return ok;
    }

    /*
     *  reutrns index in 'tree' of new vertex
     */
    ui add_vertex(T num, bool bit, ii parent, ui length) {
        tree.emplace_back(bit, parent);
        tree.back().mn = num, tree.back().mx = num;
        return prefixes[length][get_prefix(num, length)] = tree[parent].child[bit] = tree.size() - 1;
    }

    /*
     *  reutrns minimum in subtree or neutral element
     */
    T get_min(ii tree_idx) const
    {
        return tree[tree_idx].alieve ? tree[tree_idx].mn : numeric_limits<T>::max();
    }

    /*
     *  reutrns maximum in subtree or neutral element
     */
    T get_max(ii tree_idx) const
    {
        return tree[tree_idx].alieve ? tree[tree_idx].mx : numeric_limits<T>::min();
    }

    /*
     *  returns bit on position 'idx' of number 'x'
     */
    bool get_bit(T x, ui index) const {
        return (x >> (max_power - index - 1)) & 1;
    }

    /*
     *  returns prefix of number 'x'
     */
    T get_prefix(T x, ui length) const {
        return x >> (max_power - length);
    }

    /*
     *  to delete vertex
     */
    ii delete_vertex(int tree_idx, T prefix, ui length)
    {
        tree[tree_idx].alieve = false;
        prefixes[length].erase(prefix);
        return tree[tree_idx].parent;
    }

    /*
     *  update vertex
     */
    ii update_vertex(ui tree_idx)
    {
        tree[tree_idx].mn = numeric_limits<T>::max();
        tree[tree_idx].mx = numeric_limits<T>::min();
        for(bool&& bit : {0, 1})
        {
            if(is_child_alive(tree_idx, bit))
            {
                tree[tree_idx].mn = min(get_min(tree[tree_idx].child[bit]), tree[tree_idx].mn);
                tree[tree_idx].mx = max(get_max(tree[tree_idx].child[bit]), tree[tree_idx].mx);
            }
        }
        return tree[tree_idx].parent;
    }
};
const ll mxp = 31;
int n;
int q1, q2;
int test = 1;
X_fast_Trie bor(mxp);
set<int> st;
vector<int> vec;

void init()
{
    cout << "Num." << test++ << " test(init)" << endl;
    cout.flush();
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        int x = max((rand()) % (1 << mxp), 0);
        vec.eb(x);
        st.insert(x);
        bor.insert(x);
        assert(st.contains(x) == bor.contains(x));
    }
    cout << "result: OK" << endl;
}
void insert()
{
    cout << "Num." << test++ << " test(insert)" << endl;
    cout.flush();
    int cnt;
    cin >> cnt;
    n += cnt;
    for(int i = 0; i < cnt; ++i)
    {
        int x = max((rand()) % (1 << mxp), 0);
        vec.eb(x);
        st.insert(x);
        bor.insert(x);
        assert(st.contains(x) == bor.contains(x));
    }
    cout << "result: OK" << endl;
}
void find()
{
    cout << "Num." << test++ << " test(find)" << endl;
    cout.flush();
    cin >> q1;
    while(q1--)
    {
        int idx = max(rand() % n, 0);
        auto it= st.lower_bound(vec[idx]);
        ll true_value = (it == st.end()) ? -1 : *it;
        ll val = bor.lower_bound(vec[idx]);
//        cout << "q1: " << idx << ' ' << "val = " << val << ", true_val = " << true_value << endl;
        assert(val == true_value);
    }
    cout << "result: OK" << endl;
}
void erase()
{
    cout << "Num." << test++ << " test(erase)" << endl;
    cout.flush();
    cin >> q2;
    while(q2--)
    {
        int idx = max(rand() % n, 0);
        bool res = bor.erase(vec[idx]);
//        cout << "q2: " << idx << ' ' << "val = " << (res = bor.erase(vec[idx])) << ", true_val = " << st.contains(vec[idx]) << endl;
        assert(st.contains(vec[idx]) == res);
        if(st.contains(vec[idx]))
        {
            st.erase(vec[idx]);
        }
        auto it = st.lower_bound(vec[idx]);
        ll true_value = (it == st.end()) ? -1 : *it;
        ll val = bor.lower_bound(vec[idx]);
//        cout << "q22: looking for " << vec[idx] << ' ' << "ans = " << val << ", true ans = " << true_value << endl;
        assert(val == true_value);
    }
    cout << "resul: OK" << endl;
}
void solve()
{
    init();
    find();
    erase();
    insert();
    find();
    erase();
    insert();
    insert();
    erase();
    find();
    erase();
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}