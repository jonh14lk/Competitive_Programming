#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define double long double
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 2001
#define mod 1000000007

int n, l;
vector<int> adj[MAXN];
int dp[MAXN];
bool vis[MAXN];

int solve(int i)
{
  if (dp[i] != -1)
    return dp[i];
  int ret = 0;
  for (auto const &v : adj[i])
  {
    if (v < l)
    {
      ret = (ret + solve(v)) % mod;
    }
    else
    {
      ret = (ret + 1) % mod;
      vis[v] = true;
    }
  }
  return dp[i] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> l;
  for (int i = 0; i < l; i++)
  {
    int m;
    cin >> m;
    for (int j = 0; j < m; j++)
    {
      int a;
      cin >> a;
      a--;
      adj[i].pb(a);
    }
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0) << " ";
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += vis[i];
  cout << ans << endl;
  return 0;
}