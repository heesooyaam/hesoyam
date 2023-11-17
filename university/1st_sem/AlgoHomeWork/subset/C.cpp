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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> idxToName(n);
    unordered_map<string, int> NameToIdx;
    for(int i = 0; i < n; ++i)
    {
        cin >> idxToName[i];
        NameToIdx[idxToName[i]] = i;
    }
    vector<vector<bool>> notFriends(n, vector<bool> (n, false));
    for(int i = 0; i < m; ++i)
    {
        string smbd1, smbd2;
        cin >> smbd1 >> smbd2;
        notFriends[NameToIdx[smbd1]][NameToIdx[smbd2]] = true;
        notFriends[NameToIdx[smbd2]][NameToIdx[smbd1]] = true;
    }
    vector<bool> dp(1 << n);
    dp[0] = true;
    int ans = 0;
    int Team = -1;
    for(int newTeam = 1; newTeam < dp.size(); ++newTeam)
    {
        for(int newTeammate = 0; newTeammate < n; ++newTeammate)
        {
            if((1 << newTeammate) & newTeam)
            {
                int prevTeam = newTeam - (1 << newTeammate);
                bool friendship = true;        
                for(int i = 0; i < n && friendship && dp[prevTeam]; ++i)
                {
                    if((1 << i) & newTeam) friendship = friendship && !notFriends[i][newTeammate];
                }
                dp[newTeam] = dp[prevTeam] && friendship;
                if(dp[newTeam] && __popcount(newTeam) > ans)
                {
                    ans = __popcount(newTeam);
                    Team = newTeam;
                }
                break;
            }
        }
    }
    cout << ans << endl;
    vector<string> answer;
    for(int i = 0; i < n; ++i)
    {
        if((1 << i) & Team) answer.eb(idxToName[i]);
    }
    sort(all(answer));
    for(int i = 0; i < answer.size(); ++i)
    {
        cout << answer[i] << endl;
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}