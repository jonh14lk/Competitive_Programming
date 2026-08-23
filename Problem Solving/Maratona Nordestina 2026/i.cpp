#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

int bad_cycles_cnt;
set<int> bad_cycles_values;
vector<pii> adj[MAXN];
bool visited[MAXN];
int depth[MAXN];
int label[MAXN];
int delta[MAXN];
int dp[MAXN];
bool tree_edge[MAXN];
bool path_1_n_edge[MAXN];
pi parent[MAXN];

void dfs(int s, int p)
{
  visited[s] = 1;
  for (auto [x, edge_id] : adj[s])
  {
    auto [i, edge_val] = x;
    if (!visited[i]) // aresta da arvore
    {
      tree_edge[edge_id] = 1;
      parent[i] = {s, edge_id};
      label[i] = label[s] ^ edge_val;
      depth[i] = depth[s] + 1;
      dfs(i, s);
      delta[s] += delta[i];
      dp[edge_id] = delta[i];
    }
    else if (i != p && depth[s] > depth[i]) // back edge
    {
      int xor_val = label[s] ^ label[i] ^ edge_val;
      if (xor_val > 0)
      {
        bad_cycles_values.insert(xor_val);
        dp[edge_id] = 1;
        bad_cycles_cnt++;
      }
      else
      {
        dp[edge_id] = -1;
      }
      // considera esse ciclo nas arestas do caminho de s pra i
      // eh um caminho em linha reta pq eh um back edge da dfs tree
      delta[s] += dp[edge_id];
      delta[i] -= dp[edge_id];
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int x, y, c;
    cin >> x >> y >> c;
    x--, y--;
    adj[x].pb({{y, c}, i});
    adj[y].pb({{x, c}, i});
  }
  dfs(0, -1);
  string ans(m, '0');
  if (bad_cycles_values.size() > 1)
  {
    cout << ans << endl;
    return 0;
  }
  int x = n - 1;
  while (x != 0)
  {
    path_1_n_edge[parent[x].sec] = 1;
    x = parent[x].fir;
  }
  if (bad_cycles_cnt == 0)
  {
    for (int i = 0; i < m; i++)
    {
      if (dp[i] == 0)
      {
        if (path_1_n_edge[i] && label[n - 1] > 0)
          ans[i] = '1';
        else if (!path_1_n_edge[i] && label[n - 1] == 0)
          ans[i] = '1';
      }
    }
  }
  else
  {
    int x = *(bad_cycles_values.begin());
    for (int i = 0; i < m; i++)
    {
      if (dp[i] == bad_cycles_cnt)
      {
        if (path_1_n_edge[i] && label[n - 1] == x)
          ans[i] = '1';
        else if (!path_1_n_edge[i] && label[n - 1] == 0)
          ans[i] = '1';
      }
    }
  }
  cout << ans << endl;
  return 0;
}