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
#define MAXN 100005
#define mod 1000000007

int n;
vector<int> v;
vector<vector<int>> combs[6];
vector<pi> adj[MAXN];
int dp[MAXN][6];

int dfs(int i, int p, int pcolor)
{
  if (dp[i][pcolor] != -1)
    return dp[i][pcolor];
  int ret = 0, sem_cor = 0;
  for (int j = 0; j < adj[i].size(); j++)
  {
    if (adj[i][j].fir == p)
      continue;
    if (!adj[i][j].sec)
      sem_cor++;
  }
  for (auto const &k : combs[sem_cor])
  {
    int ptr = 0, ways = 1;
    bool is_valid = true;
    vector<int> s;
    if (p != -1)
      s.pb(pcolor);
    for (int j = 0; j < adj[i].size(); j++)
    {
      if (adj[i][j].fir == p)
        continue;
      int col = (!adj[i][j].sec) ? k[ptr++] : adj[i][j].sec;
      if (find(s.begin(), s.end(), col) != s.end())
      {
        is_valid = false;
        break;
      }
      s.pb(col);
    }
    if (!is_valid)
      continue;
    ptr = 0;
    for (int j = 0; j < adj[i].size(); j++)
    {
      if (adj[i][j].fir == p)
        continue;
      int col = (!adj[i][j].sec) ? k[ptr++] : adj[i][j].sec;
      ways = (ways * dfs(adj[i][j].fir, i, col)) % mod;
    }
    ret = (ret + ways) % mod;
  }
  return dp[i][pcolor] = ret;
}
void gen(int i, int sz)
{
  if (i == sz)
  {
    combs[sz].pb(v);
    return;
  }
  for (int j = 1; j <= 5; j++)
  {
    if (find(v.begin(), v.end(), j) != v.end())
      continue;
    v.pb(j);
    gen(i + 1, sz);
    v.pop_back();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    adj[b].pb({a, c});
  }
  for (int i = 0; i < n; i++)
  {
    if (adj[i].size() > 5)
    {
      cout << 0 << endl;
      return 0;
    }
  }
  for (int i = 0; i <= 5; i++)
  {
    v.clear();
    gen(0, i);
  }
  memset(dp, -1, sizeof(dp));
  cout << dfs(0, -1, 0) << endl;
  return 0;
}