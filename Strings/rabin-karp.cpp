#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 100001

vector<int> rabin_karp(string s, string t)
{
  const int p = 31;
  const int mod = 1e9 + 9;
  int n = s.size(), m = t.size();
  vector<int> pot(n);
  pot[0] = 1;
  for (int i = 1; i < n; i++)
    pot[i] = (pot[i - 1] * p) % mod;
  vector<int> pref(n + 1, 0);
  for (int i = 0; i < n; i++)
    pref[i + 1] = (pref[i] + (s[i] - 'a' + 1) * pot[i]) % mod;
  int hs = 0;
  for (int i = 0; i < m; i++)
    hs = (hs + (t[i] - 'a' + 1) * pot[i]) % mod;
  vector<int> ans;
  for (int i = 0; i + m - 1 < n; i++)
  {
    int cur_h = (pref[i + m] + mod - pref[i]) % mod;
    if (cur_h == (hs * pot[i]) % mod)
      ans.pb(i);
  }
  return ans;
}
signed main()
{
  string s, t;
  cin >> s >> t;
  vector<int> ans = rabin_karp(s, t);
  for (auto const &i : ans)
    cout << i << " " << i + t.size() - 1 << endl;
  return 0;
}
// rabin-karp for pattern matching
// given two string s and t, determine all occurrences of t in s
// 1- calcule the hash of string t
// 2- calcule the prefix hash of string s
// 3- compare every substring of s with length |t|
// 4- store all occurrences in a vector and return this vector
// complexity: O(|t| + |s|)
