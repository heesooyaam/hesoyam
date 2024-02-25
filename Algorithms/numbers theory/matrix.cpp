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

vector<ll> matrixAddition(int n1, int m1, int n2, int m2, const vector<ll>& a, const vector<ll>& b, const ll MOD = 1e9 + 7)
{
    assert(n1 == n2 && m1 == m2);

    vector<ll> ans(n1 * m1);
    
    for(int i = 0; i < n1; ++i)
    {
        for(int j = 0; j < m2; ++j)
        {
            ans[j + i * n1] = (a[j + i * n1] + b[j + i * n1]) % MOD;
        }
    }

    return ans;
}

vector<ll> matrixProduct(int n1, int m1, int n2, int m2, const vector<ll>& a, const vector<ll>& b, const ll MOD = 1e9 + 7)
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

vector<ll> matrixBinPow(unsigned int num, size_t size, const vector<ll>& mat, const ll MOD = 1e9 + 7)
{
    if(num == 1) return mat;
    
    vector<ll> ans (size * size);
    for(int i = 0; i < size; ++i) ans[i + i * size] = 1;

    vector<ll> cur = mat;

    while(num)
    {
        if(num & 1) ans = matrixProduct(size, size, size, size, ans, cur);
        cur = matrixProduct(size, size, size, size, cur, cur);
        num >>= 1;
    }
    
    return ans;
}

void solve()
{
    vector<ll> a = {1, 1, 1, 1}, b = {1, 1, 1, 1};
    print(matrixAddition(2, 2, 2, 2, a, b));
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