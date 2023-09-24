// example from trial contest
// а - греча, b - маски, c - туалетка
// из матрицы 3 на (a + b + c) выбрать самое маленькое количестводенег, которое можно потратить
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x) for(auto& val : x) cout << val << ' ';cout << endl;
#define endl '\n'    
using namespace std;

const int INF = 2e9;

void solve()
{
    int n; cin >> n;
    int a, b, c; cin >> a >> b >> c;
    vector <vector <int>> days (3, vector <int> (n));

    for(auto& vec : days)
    {
        for(int& x : vec) cin >> x;
    }

    vector<vector<int>> bought (a + 1, vector <int> (b + 1, 0));
    vector<vector<int>> newD (a + 1, vector <int> (b + 1, 0));

    int cnt = 0;
    for(int day = 1; day <= n; day++)
    {
        
        for(int fst = 0; fst <= min(day, a); fst++)
        {
            for(int snd = 0; snd <= min(b, day - fst); snd++)
            {
                int thrd = day - fst - snd;
                if(thrd > c or thrd < 0) continue;

                int var1, var2, var3; var1 = var2 = var3 = INF;
                if(fst > 0) var1 = bought[fst - 1][snd] + days[0][day - 1];
                if(snd > 0) var2 = bought[fst][snd - 1] + days[1][day - 1];
                if(thrd > 0) var3 = bought[fst][snd] + days[2][day - 1];
                
                

                //cnt++;
                //cout << cnt << ":\n" <<  "var1: " << var1 << " var2: " << var2 << " var3: " << var3 << endl;
                newD[fst][snd] = min(min(var1, var2), var3);
            }
        }
        swap(newD, bought);
        
    }

    cout << bought[a][b];
}
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}