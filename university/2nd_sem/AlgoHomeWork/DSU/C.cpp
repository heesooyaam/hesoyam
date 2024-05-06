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
struct DSU
{
public:
    DSU(int size)
            : n(size)
            , unionSize(n, 1)
            , unionsCounter(size)
            , parent(size, 0)
    {
        for(int i = 0; i < n; ++i)
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
        if(unionSize[a] > unionSize[b])
        {
            swap(a, b);
        }
        unionSize[b] += unionSize[a];
        parent[a] = b;
    }
    int unionsAmount() const
    {
        return unionsCounter;
    }
    bool areSynonyms(int w1, int w2)
    {
        return getParent(w1) == getParent(w2);
    }
    bool areAntonyms(int w1, int w2)
    {
        return getParent(w1) == getParent(w2 + n / 2);
    }
private:
    int n;
    int unionsCounter;
    vector<ll> unionSize, parent;
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> idxToWord(n);
    unordered_map<string, int> wordToIdx;
    for(int i = 0; i < n; ++i)
    {
        cin >> idxToWord[i];
        wordToIdx[idxToWord[i]] = i;
    }
    DSU dsu(2 * n);
    for(int i = 0; i < m; ++i)
    {
        int connection;
        string w1, w2;
        cin >> connection >> w1 >> w2;
        int idx1 = wordToIdx[w1], idx2 = wordToIdx[w2];
        if(connection == 1)
        {
            if(dsu.areAntonyms(idx1, idx2))
            {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            dsu.unite(idx1, idx2);
            dsu.unite(idx1 + n, idx2 + n);
        }
        else
        {
            if(dsu.areSynonyms(idx1, idx2))
            {
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
            dsu.unite(idx1, idx2 + n);
            dsu.unite(idx1 + n, idx2);
        }
    }
    for(int i = 0; i < q; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        int idx1 = wordToIdx[s1], idx2 = wordToIdx[s2];
        if (dsu.areSynonyms(idx1, idx2))
        {
            cout << 1 << endl;
        }
        else if(dsu.areAntonyms(idx1, idx2))
        {
            cout << 2 << endl;
        }
        else cout << 3 << endl;
    }
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