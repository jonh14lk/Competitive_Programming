#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

int curr_hash = 1;
map<vector<int>, int> mp;
int dp[MAXN];
int fat[MAXN];
int invfat[MAXN];
vector<int> adj[MAXN];

int modpow(int a, int b, int m)
{
  int ans = 1;
  a %= m;
  while (b)
  {
    if (b & 1)
      ans = (ans * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return ans;
}
int moddiv(int a, int b, int m)
{
  return (a * modpow(b, m - 2, mod)) % mod;
}
int arranjo(int n, int k)
{
  if (k > n)
    return 0;
  return (fat[n] * invfat[n - k]) % mod;
}
int dfs(int s, int p)
{
  map<int, int> cnt;
  vector<int> child;
  dp[s] = 1;
  for (auto const &v : adj[s])
  {
    if (v != p)
    {
      child.pb(dfs(v, s));
      cnt[child.back()]++;
      dp[s] = (dp[s] * dp[v]) % mod;
    }
  }
  sort(child.begin(), child.end());
  if (!mp[child])
    mp[child] = curr_hash++;
  dp[s] = (dp[s] * arranjo(26, child.size())) % mod;
  for (auto const &i : cnt)
    dp[s] = (dp[s] * invfat[i.sec]) % mod;
  return mp[child];
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  fat[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    fat[i] = (fat[i - 1] * i) % mod;
    invfat[i] = modpow(fat[i], mod - 2, mod);
  }
  dfs(0, -1);
  cout << dp[0] << endl;
  return 0;
}
