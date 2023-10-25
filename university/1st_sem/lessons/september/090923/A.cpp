// найти подмножество наибольшей длины для которого выполняется 2 * min >= max
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x); for(auto& val : x){cout << val << ' ';}cout << endl;
#define input(x); for(auto& val : x){cin >> val;}
#define endl '\n'   

void solve()
{
    int len;
    cin >> len;
    vector <int> array (len);
    input(array);
    sort(all(array));
    int l, r; l = 0; r = 1;
    int ans = 0;
    for(; l < len + 1; l++)
    {
        for(; r < len; r++)
        {
            if(array[l] * 2 >= array[r])
            {
                ans = max(r - l + 1, ans);
                continue;
            }
            else break;
        }
    }
    cout << ans << endl;
}   
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}