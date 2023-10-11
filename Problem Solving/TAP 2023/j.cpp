#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

int ans;
bool broken;
vector<int> adj[MAXN];
vector<int> g_in[MAXN];
vector<int> g_out[MAXN];
int with_dist[MAXN];
int in[MAXN];
int out[MAXN];
int dist[MAXN];
bool on[MAXN];

void prop(int x)
{
  on[x] = 0;
  with_dist[dist[x]]--;
  if (with_dist[dist[x]] == 0)
  {
    broken = 1;
  }
  if (with_dist[dist[x]] == 1)
  {
    ans++;
  }
  for (auto const &y : g_in[x])
  {
    if (on[y])
    {
      out[y]--;
      if (out[y] == 0)
        prop(y);
    }
  }
  for (auto const &y : g_out[x])
  {
    if (on[y])
    {
      in[y]--;
      if (in[y] == 0)
        prop(y);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  for (int i = 1; i < n; i++)
  {
    dist[i] = 1e9;
  }
  dist[0] = 0;
  {
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
      int x = q.front();
      q.pop();
      for (auto const &y : adj[x])
      {
        if (dist[y] > dist[x] + 1)
        {
          dist[y] = dist[x] + 1;
          q.push(y);
        }
      }
    }
  }
  {
    queue<int> q;
    vector<bool> vis(n, 0);
    q.push(n - 1);
    vis[n - 1] = 1;
    while (!q.empty())
    {
      int x = q.front();
      q.pop();
      on[x] = 1;
      with_dist[dist[x]]++;
      for (auto const &y : adj[x])
      {
        if (dist[y] == dist[x] - 1)
        {
          out[y]++;
          in[x]++;
          g_out[y].pb(x);
          g_in[x].pb(y);
          if (!vis[y])
          {
            vis[y] = 1;
            q.push(y);
          }
        }
      }
    }
  }
  for (int i = 1; i < n - 1; i++)
  {
    if (on[i] && with_dist[dist[i]] == 1)
      ans++;
  }
  cout << ans << " ";
  for (int i = 0; i < k; i++)
  {
    int x;
    cin >> x;
    x--;
    if (broken)
    {
      cout << "-1 ";
      continue;
    }
    if (on[x])
      prop(x);
    if (broken)
      cout << "-1 ";
    else
      cout << ans << " ";
  }
  cout << endl;
  return 0;
}