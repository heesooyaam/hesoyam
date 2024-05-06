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
template<typename T>
class SparceTable
{
public:
    SparceTable(const vector<T>& vec)
    : n(vec.size() + 1)
    , power(__lg(n) + 1)
    , table(power, vector<T> (n, numeric_limits<T>::max()))
    {
        build(vec);
//        cout << "Builded. Power = " << power << ". Size = " << n << endl;
    }
    T getMin(size_t l, size_t r) const
    {
        int p = __lg(r - l + 1);
//        cout << p << ' ' << "1st segment: " << l << ", " << l + (1 << p) - 1 << ", 2nd seg: " << r - (1 << p) + 1 << ", " << r << endl;
        return ((table[p][l] < table[p][r - (1 << p) + 1]) ? table[p][l] : table[p][r - (1 << p) + 1]);
    }
private:
    const size_t n;
    const size_t power;
    vector<vector<T>> table;
    void build(const vector<T>& vec)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            table[0][i] = vec[i];
        }
        for(int p = 0; p < power - 1; ++p)
        {
            for(int i = 0; i + (1 << (p + 1)) < n; ++i)
            {
                table[p + 1][i] = (table[p][i] < table[p][i + (1 << p)]) ? table[p][i] : table[p][i + (1 << p)];
            }
        }
    }
};

void solve()
{
    srand(time(0));
    size_t size = rand() % 1'000;
    vector<int> vec(size);
    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i] = rand();
    }
//    print(vec);
    auto mn = [&](int l, int r)
    {
        int mn = numeric_limits<int>::max();
        for(int i = l; i < r + 1; ++i)
        {
            mn = min(mn, vec[i]);
        }
        return mn;
    };
    SparceTable<int> ST(vec);
    int tests = rand() % 1'000;
    for(int i = 0; i < tests; ++i)
    {
        int l = rand() % vec.size();
        int r = rand() % vec.size();
        if(l > r) swap(l, r);
//        cout << "test No" << i + 1 << ", l = " << l << ", r = " << r << " ..." << endl;
        int wait = mn(l, r);
        int cur = ST.getMin(l, r);
//        cout << "wait for answer = " << wait << ", cur answer = " << cur << endl;
        assert(wait == cur);
//        cout << "OK" << endl;
    }
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}