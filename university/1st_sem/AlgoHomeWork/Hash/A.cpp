#include <bits/stdc++.h> 
using ll = long long; 
using ld = long double; 
using ull = unsigned long long; 
 
using namespace std; 
 
const ll MOD = 1e9 + 123; 
const ll K = 29; 
 
bool comp(string& a, string& b) { 
 return a.size() < b.size(); 
} 
 
void solve() { 
 ifstream in("substr.in"); 
 ofstream out("substr.out"); 
 ll n; 
 in >> n; 
 vector<string> v(n); 
 for (ll i = 0; i < n; ++i) { 
  in >> v[i]; 
 } 
 sort(v.begin(), v.end(), comp); 
 vector<ll> pows(v.back().size(), 1); 
 for (ll i = 1; i < pows.size(); ++i) { 
  pows[i] = pows[i - 1] * K % MOD; 
 } 
 vector<vector<ll>> prefixHash(n); 
 for (ll i = 0; i < n; ++i) { 
  prefixHash[i].resize(v[i].size() + 1, 0); 
  for (ll j = 1; j <= v[i].size(); ++j) { 
   prefixHash[i][j] = ((v[i][j - 1] - 'a' + 1) * pows[j - 1] % MOD + prefixHash[i][j - 1]) % MOD; 
  } 
 } 
 ll l = 1; 
 ll r = v[0].size() + 1; 
 while (l + 1 < r) { 
  ll mid = (l + r) >> 1; 
  set<ll> s1; 
  for (ll i = 1; i + mid - 1 <= v[0].size(); ++i) { 
   s1.insert((prefixHash[0][i + mid - 1] - prefixHash[0][i - 1] + MOD) % MOD * pows[pows.size() - i] % MOD); 
  } 
  for (ll i = 1; i < n; ++i) { 
   set<ll> s2; 
   for (ll j = 1; j + mid - 1 <= v[i].size(); ++j) { 
    ll h = (prefixHash[i][j + mid - 1] - prefixHash[i][j - 1] + MOD) % MOD * pows[pows.size() - j] % MOD; 
    if (s1.find(h) != s1.end()) { 
     s2.insert(h); 
    } 
   } 
   swap(s1, s2); 
   if (s1.size() == 0) { 
    break; 
   } 
  } 
  if (s1.size() != 0) { 
   l = mid; 
  } 
  else { 
   r = mid; 
  } 
 } 
 set<ll> s1; 
 for (ll i = 1; i + l - 1 <= v[0].size(); ++i) { 
  s1.insert((prefixHash[0][i + l - 1] - prefixHash[0][i - 1] + MOD) % MOD * pows[pows.size() - i] % MOD); 
 } 
 for (ll i = 1; i < n; ++i) { 
  set<ll> s2; 
  for (ll j = 1; j + l - 1 <= v[i].size(); ++j) { 
   ll h = (prefixHash[i][j + l - 1] - prefixHash[i][j - 1] + MOD) % MOD * pows[pows.size() - j] % MOD; 
   if (s1.find(h) != s1.end()) { 
    s2.insert(h); 
   } 
  } 
  swap(s1, s2); 
 } 
 for (ll i = 1; i + l - 1 <= v[0].size(); ++i) { 
  if (s1.find((prefixHash[0][i + l - 1] - prefixHash[0][i - 1] + MOD) % MOD * pows[pows.size() - i] % MOD) != s1.end()) { 
   string output; 
   for (ll j = i; j <= i + l - 1; ++j) { 
    output.push_back(v[0][j - 1]); 
   } 
   out << output; 
   return; 
  } 
 } 
} 
 
int main() { 
 ios_base::sync_with_stdio(0); 
 cin.tie(0); 
 cout.tie(0); 
 ll t = 1; 
 //cin >> t; 
 while (t--) { 
  solve(); 
 } 
 return 0; 
}
