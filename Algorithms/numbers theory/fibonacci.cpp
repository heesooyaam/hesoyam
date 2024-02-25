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


vector<ll> matrixProduct(int n1, int m1, int n2, int m2, vector<ll>& a, vector<ll>& b, const ll MOD = 1e9 + 7)
{
    assert(n2 == m1);
    
    int n = n1, m = m2;

    vector<ll> mat(n * m);

    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            for(int k = 0; k < n2; ++k)
            {
                mat[j + i * n] += a[k + i * m1] * b[j + k * n2] % MOD;
            }
        }
    }

    return mat;
}
ll fastFib(unsigned int num, const ll MOD = 1e9 + 7)
{
    num -= 1;
    vector<ll> ans = {1, 0, 0, 1};
    vector<ll> cur = {0, 1, 1, 1};
    while(num)
    {
        if(num & 1) ans = matrixProduct(2, 2, 2, 2, ans, cur);
        cur = matrixProduct(2, 2, 2, 2, cur, cur);
        num >>= 1;
    }
    vector<ll> fib = {0, 1};
    return matrixProduct(1, 2, 2, 2, fib, ans)[1];
}


class fib
{
public:

    fib(unsigned int n, const ll MOD = 1'000'000'007)
    : n(n)
    , MOD(MOD)
    , val(fastFib())
    {}
    operator ll() const
    {
        return this->val;
    }
    operator int() const
    {
        assert(MOD <= INT_MAX);
        return this->val;
    }
private:
    unsigned int n;
    const ll MOD;
    ll val;
    vector<ll> matrixProduct(int n1, int m1, int n2, int m2, vector<ll>& a, vector<ll>& b, const ll MOD = 1e9 + 7)
    {
        assert(n2 == m1);
        
        int n = n1, m = m2;

        vector<ll> mat(n * m);

        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                for(int k = 0; k < n2; ++k)
                {
                    mat[j + i * n] += a[k + i * m1] * b[j + k * n2] % MOD;
                }
            }
        }
        return mat;
    }
    ll fastFib()
    {
        unsigned num = n;
        num -= 1;
        vector<ll> ans = {1, 0, 0, 1};
        vector<ll> cur = {0, 1, 1, 1};
        while(num)
        {
            if(num & 1) ans = matrixProduct(2, 2, 2, 2, ans, cur);
            cur = matrixProduct(2, 2, 2, 2, cur, cur);
            num >>= 1;
        }
        vector<ll> fib = {0, 1};
        return matrixProduct(1, 2, 2, 2, fib, ans)[1];
    }
};

void solve()
{
    int n;
    cin >> n;
    cout << ll(fib(n)) << endl;
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