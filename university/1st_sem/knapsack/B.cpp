#include <bits/stdc++.h>

using namespace std;

const int n = 9;
const int L = 840;

typedef long long ll;

ll dp[n][L * n];
ll W;
ll cnt[n];

int main()
{
	cin >> W;
	for(int i = 0; i < 8; i++) cin >> cnt[i];
	for(int i = 0; i < n; i++) for(int j = 0; j < L * n; j++) dp[i][j] = -1;
	dp[0][0] = 0;
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < L * n; j++)
		{
			if(dp[i][j] == -1) continue;
			int b = L / (i + 1);
			if(cnt[i] < b)
				b = cnt[i];
			for(int k = 0; k <= b; k++)
			{
				ll& d = dp[i + 1][j + k * (i + 1)];
				d = max(d, dp[i][j] + (cnt[i] - k) / (L / (i + 1)));
			}
		}
	}
	ll ans = 0;
	for(int j = 0; j < L * n; j++)
	{
		if(j > W || dp[8][j] == -1) continue;
		ans = max(ans, j + L * (min(dp[8][j], (W - j) / L)));
	}
	cout << ans << endl;
}