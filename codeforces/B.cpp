#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
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

/*
Есть последовательность запросов пользователей, каждый запрос —
это пара (time, userId), запросы всегда приходят в отсортированном
по времени порядке.
Нужно уметь быстро отвечать: "сколько за последние k секунд было
пользователей, которые задали >= limit запросов". k > 0, limit > 0.
k = 5
now = 5
// 1..5
*/
// time1 < time2
class UserStatistics
{
public:
    UserStatistics(int k, int limit)
            : windowSize(k)
            , limit(limit)
            , robotsCounter(0) {}

    void event(int now, int userId)
    {

        int newActions = ++actions[userId];

        if(newActions == limit)
        {
            ++robotsCounter;
        }

        events.push({now, userId});
        clearEvents(now);
    }

    int robotCount(int now) const {
        return robotsCounter;
    }

    struct Event
    {
        int time, userId;
    };
private:
    const int windowSize, limit;
    int robotsCounter;
    unordered_map<int, int> actions;
    queue<Event> events;
    void clearEvents(int to)
    {
        // target: to - windowSize + 1
        while(!events.empty() && events.front().time < to - windowSize + 1)
        {
            int curUser = events.front().userId;

            int newActions = --actions[curUser];

            if(newActions + 1 == limit)
            {
                --robotsCounter;
            }

            if(newActions == 0)
            {
                actions.erase(curUser);
            }

            events.pop();
        }
    }
};
void solve()
{

}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    int ttest = 1;
    cin >> ttest;
    while(ttest--) solve();
    return 0;
}

