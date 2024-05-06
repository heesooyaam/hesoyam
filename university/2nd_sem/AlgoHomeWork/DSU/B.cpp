//
// Created by topcr on 03.04.2024.
//
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
size_t unionsCounter = 0;
class DSU
{
public:
    explicit DSU(size_t size, size_t indexation = 0)
    : n(size)
    , unionSize(n + indexation, 0)
    , parent(n + indexation, 0)
    {
        for(int i = indexation; i < n + indexation; ++i)
        {
            parent[i] = i;
        }
    }
    int getParent(int v)
    {
        if(parent[v] == v) return v;

        parent[v] = getParent(parent[v]);

        return parent[v];
    }
    void unite(int a, int b)
    {
        a = getParent(a);
        b = getParent(b);
        if(a == b) return;
        --unionsCounter;
//        if(unionSize[a] > unionSize[b])
//        {
//            swap(a, b);
//        }
//        unionSize[b] += unionSize[a];
        parent[a] = b;
    }
    bool areInTheSameUnion(int a, int b)
    {
        return getParent(a) == getParent(b);
    }
    size_t unionsAmount() const
    {
        return unionsCounter;
    }
    size_t n;
    vector<int> unionSize;
    vector<int> parent;
};
unordered_map<char, string> toBinary;
void solve()
{
    int n, m;
    cin >> n >> m;
    string cur, prev(m, '0');
    auto prepareString = [&](string& s)
    {
        s.clear();
        for(int i = 0; i < m / 4; ++i)
        {
            char symb;
            cin >> symb;
            s += toBinary[symb];
        }
    };
    vector<DSU> dsu(2, DSU(2 * m, 1));
    int ans = 0;
    for(int i = 0, q = 0; i < n; ++i, q ^= 1)
    {
        prepareString(cur);
        for(int j = 0; j < m; ++j)
        {
            assert(dsu[q ^ 1].parent[j + m] >= m);
            dsu[q].parent[j] = dsu[q ^ 1].parent[j + m] % m;
            dsu[q].parent[j + m] = j + m;
//            dsu[q].unionSize[j] = dsu[q ^ 1].unionSize[j + m];
//            dsu[q].unionSize[j + m] = (cur[j] == '1');
            unionsCounter += (cur[j] == '1');
        }
        for(int j = 0; j < m; ++j)
        {
            if(cur[j] == '0') continue;
            if(j && cur[j] == cur[j - 1]) dsu[q].unite(m + j - 1, m + j);
            if(cur[j] == prev[j]) dsu[q].unite(j, m + j);
        }
        swap(cur, prev);
    }
    cout << unionsCounter << endl;
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
    toBinary['0'] = "0000"; toBinary['1'] = "0001"; toBinary['2'] = "0010"; toBinary['3'] = "0011";
    toBinary['4'] = "0100"; toBinary['5'] = "0101"; toBinary['6'] = "0110"; toBinary['7'] = "0111";
    toBinary['8'] = "1000"; toBinary['9'] = "1001"; toBinary['A'] = "1010"; toBinary['B'] = "1011";
    toBinary['C'] = "1100"; toBinary['D'] = "1101"; toBinary['E'] = "1110"; toBinary['F'] = "1111";
//    cin >> ttest;
    while(ttest--) solve();
    return 0;
}