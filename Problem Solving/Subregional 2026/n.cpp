#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1001
#define mod 1000000007

int n;
bool vis[MAXN];
vector<pi> adj[MAXN];
vector<int> ans[MAXN];

void dfs(int s, int k, int ban)
{
  vis[s] = 1;
  ans[s].pb(k);
  for (auto [u, id] : adj[s])
  {
    if (id == ban)
      continue;
    if (!vis[u])
      dfs(u, k, ban);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  vector<pi> edges;
  for (int i = 0; i < (n - 1); i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb({v, i});
    adj[v].pb({u, i});
    edges.pb({u, v});
  }
  int key_id = 1;
  for (int i = 0; i < (n - 1); i++)
  {
    for (int i = 0; i < n; i++)
      vis[i] = 0;
    dfs(edges[i].fir, key_id, i);
    dfs(edges[i].sec, key_id + 1, i);
    key_id += 2;
  }
  cout << key_id << endl;
  for (int i = 0; i < n; i++)
  {
    cout << ans[i].size() << " ";
    for (auto const &j : ans[i])
      cout << j << " ";
    cout << endl;
  }
  return 0;
}