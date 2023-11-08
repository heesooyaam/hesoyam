#include <bits/stdc++.h>
using namespace std;
void solve()
{
    int n, k; cin >> n >> k;
    vector <int> vec (n);
    for(int i = 0; i < n; i++) cin >> vec[i];
    //sort(vec.begin(), vec.end());
    long long ans = 0;
    int last = 1;
    for(int i = 0; i < n; i++)
    {
        for(; vec[last] - vec[i] <= k and last <= n - 1; last++){}
        int q = (last - 1) - i;
        if(q >= 2) ans += 1ll * q * (q - 1) / 2;
    }
    cout << ans;
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}