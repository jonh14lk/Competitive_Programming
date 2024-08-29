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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000001

// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/hashingLargeMod.cpp
const int MOD = (1ll << 61) - 1;
int P;
int mulmod(int a, int b)
{
  const static int LOWER = (1ll << 30) - 1, GET31 = (1ll << 31) - 1;
  int l1 = a & LOWER, h1 = a >> 30, l2 = b & LOWER, h2 = b >> 30;
  int m = l1 * h2 + l2 * h1, h = h1 * h2;
  int ans = l1 * l2 + (h >> 1) + ((h & 1) << 60) + (m >> 31) + ((m & GET31) << 30) + 1;
  ans = (ans & MOD) + (ans >> 61), ans = (ans & MOD) + (ans >> 61);
  return ans - 1;
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int uniform(int l, int r)
{
  uniform_int_distribution<int> uid(l, r);
  return uid(rng);
}
struct string_hashing
{
  vector<int> h, p;
  string_hashing() {}
  string_hashing(string s) : h(s.size()), p(s.size())
  {
    p[0] = 1, h[0] = s[0];
    for (int i = 1; i < s.size(); i++)
      p[i] = mulmod(p[i - 1], P), h[i] = (mulmod(h[i - 1], P) + s[i]) % MOD;
  }
  int get(int l, int r)
  {
    int hash = h[r] - (l ? mulmod(h[l - 1], p[r - l + 1]) : 0);
    return hash < 0 ? hash + MOD : hash;
  }
  int append(int h, int hb, int blen)
  {
    return (hb + mulmod(h, p[blen])) % MOD;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  P = uniform(256, MOD - 1);
  vector<string_hashing> v(n);
  vector<string_hashing> v_rev(n);
  vector<int> sz(n);
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    v[i] = string_hashing(s);
    sz[i] = s.size();
    ans += (s.size() * n);
    ans += (s.size() * n);
    reverse(s.begin(), s.end());
    v_rev[i] = string_hashing(s);
  }
  unordered_map<int, int> mp;
  for (int i = 0; i < n; i++)
  {
    for (int j = 1; j <= sz[i]; j++)
      mp[v[i].get(0, j - 1)]++;
  }
  for (int i = 0; i < n; i++)
  {
    int acc = 0;
    for (int j = sz[i]; j >= 1; j--)
    {
      int curr = mp[v_rev[i].get(0, j - 1)];
      ans -= ((curr - acc) * j * 2);
      acc = curr;
    }
  }
  cout << ans << endl;
}
// https://codeforces.com/contest/1902/problem/E
// solucao usando hash mod 2^61 - 1