//example from trial contest
// Вася очень любит математику, а кроме математики он любит играть в шахматы.
// Недавно ему приснился кошмарный сон, в котором он скакал на коне по шахматному полю, а за ним гнались злые монстры.
// На поле то тут, то там были расставлены ловушки, а также на одной из клеток поля была дверь, через которую можно было прорваться в следующий сон из этого кошмара.
// Помогите Васе посчитать, за сколько ходов конем он сможет выбраться из кошмара.

//В первой строке входных данных задано два целых числа n и k, 8 ≤ n ≤ 1000,  — размер доски (n× n клеток) и количество ловушек на поле.
// В последующих k строках входных данных задано по два целых числа xi yi, 1 ≤ xi, yi ≤ n, 1 ≤ i ≤ k — позиция каждой ловушки на поле.
// В следующей строке входных данных задано два целых числа x0 y0, 1 ≤ x0, y0 ≤ n — начальная позицию Васи на доске.
// В последней строке входных данных задано два целых числа xf yf, 1 ≤ xf, yf ≤ n — позиция спасительной двери на доске.



#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define eb(x) emplace_back(x)
#define all(x) (x).begin(),(x).end()
#define print(x) for(auto& val : x) cout << val << ' ';cout << endl;
#define endl '\n'    
using namespace std;

void solve()
{
    int n, k; cin >> n >> k;

    //cout << "!!! " << n << " " << k << endl;
    vector <vector<bool>> used (n + 1, vector <bool> (n + 1, 0));

    while(k--)
    {
        int x, y; cin >> x >> y;
        //cout << "banned point: " << x  << ' ' << y << endl;
        used[x][y] = true;
    }

    

    pair <int, int> start;
    cin >> start.first >> start.second;

    //cout << "start: " << start.first << ' ' << start.second << endl << endl;;

    pair <int, int> finish;
    cin >> finish.first >> finish.second;
    //cout << "finish: " << finish.first << ' ' << finish.second << endl << endl;;

    vector <pair<int, int>> moves {{-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

    vector <vector<int>> dist (n + 1, vector <int> (n + 1, -1));
    
    queue <pair<int, int>> q;
    q.push(start);
    
    dist[start.first][start.second] = 0;
    used[start.first][start.second] = true;
    
    while(!q.empty())
    {
        
        int nowX = q.front().first;
        int nowY = q.front().second;
        q.pop();

       // cout << nowX << ' ' << nowY << endl;
        for(auto& [dx, dy] : moves)
        {
            int curX = nowX + dx;
            int curY = nowY + dy;

            if(curX > n or curX < 1 or curY > n or curY < 1 or used[curX][curY]) continue;

            if(finish.first == curX and finish.second == curY)
            {
                cout << dist[nowX][nowY] + 1;
                return;
            }

            dist[curX][curY] = dist[nowX][nowY] + 1;
            used[curX][curY] = true;

            q.push(make_pair(curX, curY));
        }
    }

    cout << -1;
}   
int main()
{
    ios :: sync_with_stdio(0); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
    return 0;
}