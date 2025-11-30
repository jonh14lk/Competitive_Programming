#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

int n, m, guy;
vector<int> ans;
vector<int> adj[1005];
int dp[1005][1005];
int vis[1005][1005];
int op[1005][1005];

int solve(int i, int j)
{
  if (i > guy)
    return 0;
  if ((i + n) == j)
    return 0;
  if (i == guy && j == (n + n - 1))
    return 1;
  if (vis[i][j] == guy)
    return dp[i][j];
  int ans = 0;
  if ((i + n) > j) // move o j
  {
    for (auto const &nxt : adj[j])
    {
      if (solve(i, nxt))
      {
        ans = 1;
        op[i][j] = nxt;
      }
    }
  }
  else // move o i
  {
    for (auto const &nxt : adj[i])
    {
      if (solve(nxt, j))
      {
        ans = 1;
        op[i][j] = nxt;
      }
    }
  }
  vis[i][j] = guy;
  return dp[i][j] = ans;
}
void rec(int i, int j)
{
  if (i == guy && j == (n + n - 1))
    return;
  if ((i + n) > j) // move o j
  {
    ans.pb(op[i][j]);
    rec(i, op[i][j]);
  }
  else // move o i
  {
    ans.pb(op[i][j]);
    rec(op[i][j], j);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  if (n == 1)
  {
    cout << "*\n";
    return 0;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
  }
  memset(vis, -1, sizeof(vis));
  for (int i = n; i < n + n; i++)
  {
    guy = i;
    if (solve(0, i))
    {
      rec(0, i);
      ans.pb(0);
      ans.pb(i);
      sort(ans.begin(), ans.end());
      ans.erase(unique(ans.begin(), ans.end()), ans.end());
      cout << ans.size() << endl;
      for (auto const &i : ans)
        cout << i + 1 << " ";
      cout << endl;
      return 0;
    }
  }
  cout << "*\n";
  return 0;
}