#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define endl '\n'

const int INF = 2e9;

void solve()
{
    int n; cin >> n;

    vector <int> vec(n);
    input(vec);

    vector <int> d(n, INF); // for e.g., d[i] is the lowest of last elements in subsequences with lenght i. we start with d[0] = -INF and d[1..n] = +INF
    d[0] = -INF;
    vector <int> pos(n, -1); // positions of elements in d[0..n] in array vec(n); for e.g., pos[i] - is the position of optimal last element from subsec-ce with lenght i in vec(n) 
    vector <int> prv(n, -1); // position of previous element in main array vec(n)

    // what should we do?
    // first of all we should notice, that d[i] at least is equal to d[i - 1], so d[i - 1] <= d[i]. 
    // secondly, every element vec[1..n] updates only one position in d[1..n], which can be found using upper_bound() on d[1..n]
    // to be more exact, we find first element d[len], which is bigger then vec[i] and do this: now d[len] = a[i], pos[len] = i, prev[i] = pos[i - 1]

    int length = 0;

    for(int i = 0; i < n; i++)
    {
        int mxLen = upper_bound(all(d), vec[i]) - vec.begin();
        // if we want to find increasing subsecuence, we should prove if vec[i] is equal to d[mxLen - 1]
        // !!!!!!!!!!if(vec[i] == d[mxLen - 1]) continue;!!!!!!!!!!!!!!!!!!!
        length = max(length, mxLen);
        d[mxLen] = vec[i];
        pos[mxLen] = i;
        prv[i] = pos[i - 1];
    }
    
    // how to restore?
    // let's make array ans(length), start with cur_idx = pos[length] and support it while cur_idx isn't -1, so ans[0] = vec[cur_idx]
    // to go further: cur_idx = prv[cur_idx], ans[i] = vec[cur_idx] and so on
    // don't forget to reverse answer, because we started from the end of subsequence
    
    vector <int> ans(length);
    int cur_idx = pos[length];
    while(cur_idx != -1)
    {
        ans.eb(vec[cur_idx]);
        cur_idx = prv[cur_idx];
    }

    reverse(all(ans));

    print(ans);


}   
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}