#include <bits/stdc++.h>
using namespace std;

bool mydfs(vector<vector<int>>& g, vector <bool>& used, vector<int>& ans, int cur, int finish)
{
    // поиск
    if(cur == finish)
    {
        ans.push_back(cur);
        return true;
    }

    for(int& to : g[cur])
    {
        if(used[to]) continue;
        used[to] = true;
        if(mydfs(g, used, ans, to, finish))
        {
            ans.push_back(cur);
            return true;
        }
    }

    return false;
}
