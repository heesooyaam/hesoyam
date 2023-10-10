#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
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
bool cmp(vector<int>& a, vector<int>& b)
{
    return a[0] < b[0];
}
void solve()
{
    int n, m;
    // n - competetitors
    // m - questions
    cin >> n >> m;
    vector<int> victories(n + 1);
    //competitor i has victories[i] victories
    deque<pair<int, int>> q;
    vector<int> power (n + 1);
    // q - current sequence of competitors
    for(int i = 1; i < n + 1; ++i)
    {
        cin >> power[i];
        q.eb(power[i], i);
    }
    vector <vector<int>> questions (m, vector<int> (3));
    // questions - array of requests: question[№ of question][0 - rounds were played, 1 - number of competitor, 2 - request's number] = 
    for(int i = 0; i < m; ++i)
    {
        cin >> questions[i][1] >> questions[i][0];
        questions[i][2] = i;
    }
    
    vector <int> ans(m);
    sort(all(questions), cmp);
    int rounds = 0;
    int ptr = 0;
    while(q.front().ff != n)
    {
        for(; ptr < ans.size() && questions[ptr][0] == rounds; ++ptr)
        {
            ans[questions[ptr][2]] = victories[questions[ptr][1]];
        }
        auto first = q.front();
        q.ppf();
        if(first.ff > q.front().ff)
        {
            auto second = q.front();
            q.ppf();
            q.pb(second);
            q.pf(first);
            ++victories[first.ss];
            //cout << first.ss<< ' ' << rounds << endl;
        }
        else
        {
            ++victories[q.front().ss];
            q.pb(first);
            //cout << q.front().ss << ' ' << rounds << endl;
        }
        ++rounds;
    }
    
    for(; ptr < ans.size(); ++ptr)
    {
        if(power[questions[ptr][1]] == n)
        {
            ans[questions[ptr][2]] = victories[questions[ptr][1]] + questions[ptr][0] - rounds;
        }
        else ans[questions[ptr][2]] = victories[questions[ptr][1]];
    }

    for(int i = 0; i < m; ++i)
    {
        cout << ans[i] << endl;
    }
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    while(t--) solve();
    return 0;
}