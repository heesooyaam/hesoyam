#include <bits/stdc++.h>
using namespace std;

int main()
{
    const int MAXN = 1e5;
    vector<int> prime2(MAXN, 0);
	prime2[0] = prime2[1] = 1;
	for (int i = 2; i * i <= MAXN; ++i) {
		if (prime2[i]) continue;

		for (int j = i; i * j < MAXN; ++j) {
			prime2[j * i] = i;
		}
	}
	for (int i = 0; i < MAXN; ++i) {
		if (prime2[i] == 0) prime2[i] = i;
	}


	int n;
	cin >> n;
	int ans = 1;
	while (n > 1) {
		int cnt = 0;
		int k = prime2[n];
		while (n % k == 0) {
			cnt++;
			n /= k;
		}
		ans *= (cnt + 1);
		// (p1, cnt1),(p2, cnt2), (p3, cnt3)...
	}
	// ans ~ O(N^(1/3))
}