#include <bits/stdc++.h>
using namespace std;

void bfs(vector<vector<int>>& g, vector <int>& dist, int start, int finish)
{
    queue <int> q;
    q.push(start);
    dist[start] = 0;
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        for(int& to : g[cur])
        {
            if(to == finish)
            {
                dist[finish] = dist[cur] + 1;
                return;
            }
            if(dist[to] == -1)
            {
                dist[to] = dist[cur] + 1;
                q.push(to);
            }
        }
    }
}