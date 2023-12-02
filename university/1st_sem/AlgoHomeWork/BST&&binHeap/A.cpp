#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
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
void Insert(vector<string>& ans, int x)
{
    string s = "insert ";
    s += to_string(x);
    ans.eb(s);
}
void getMin(vector<string>& ans, int x)
{
    string s = "getMin ";
    s += to_string(x);
    ans.eb(s);
}
void removeMin(vector<string>& ans)
{
    string s = "removeMin";
    ans.eb(s);
}
void solve()
{
    int n; 
    cin >> n;
    vector<pair<int, int>> actions(n + 1);
    for(int i = 1; i <= n; ++i)
    {
        string s;
        int x;
        cin >> s;
        if(s.front() == 'i')
        {
            cin >> x;
            actions[i] = {1, x};
        }
        else if(s.front() == 'g')
        {
            cin >> x;
            actions[i] = {2, x};
        }
        else
        {
            actions[i] = {3, 0};
        }
    }
    // cout << endl << "what was written: " << endl;
    // for(int i = 1; i <= n; ++i)
    // {
    //     cout << actions[i].ff << ' ' << actions[i].ss << endl;
    // }
    // cout << endl << endl;
    priority_queue<int, std::vector<int>, std::greater<int>> q;
    vector<string> ans;
    for(int i = 1; i <= n; ++i)
    {
        if(actions[i].ff == 1)
        {
            q.push(actions[i].ss);
            Insert(ans, actions[i].ss);
        }
        else if(actions[i].ff == 2)
        {
            if(!q.empty() && q.top() == actions[i].ss)
            {
                getMin(ans, q.top());
                continue;
            }

            while(!q.empty() && q.top() < actions[i].ss)
            {
                removeMin(ans);
                q.pop();
            }

            if(!q.empty() && q.top() == actions[i].ss)
            {
                getMin(ans, q.top());
            }
            else
            {
                Insert(ans, actions[i].ss);
                q.push(actions[i].ss);
                getMin(ans, q.top());
            }
        }
        else
        {
            if(!q.empty())
            {
                q.pop();
                removeMin(ans);
            }
            else
            {
                Insert(ans, 1);
                removeMin(ans);
            }
        }
    }
    cout << ans.size() << endl;
    for(auto& s : ans) cout << s << endl;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}