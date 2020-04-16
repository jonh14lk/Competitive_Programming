// LCA com dp
#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXL 20
#define MAXN 50500

int n, m;
int father[MAXN];
int level[MAXN];
int ancestral[MAXN][MAXL];
vector<int> adj[MAXN];

int lca(int u, int v)
{
  if (level[u] < level[v])
    swap(u, v);
  for (int i = MAXL - 1; i >= 0; i--)
    if (level[u] - (1 << i) >= level[v])
      u = ancestral[u][i];
  if (u == v)
    return u;
  for (int i = MAXL - 1; i >= 0; i--)
    if (ancestral[u][i] != -1 && ancestral[u][i] != ancestral[v][i])
    {
      u = ancestral[u][i];
      v = ancestral[v][i];
    }
  return father[u];
}
void dfs(int u)
{
  for (int i = 0; i < adj[u].size(); i++)
  {
    int v = adj[u][i];
    if (level[v] == -1)
    {
      father[v] = u;
      level[v] = level[u] + 1;
      dfs(v);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  memset(father, -1, sizeof(father));
  memset(level, -1, sizeof(level));
  memset(ancestral, -1, sizeof(ancestral));
  level[1] = 0;
  dfs(1);
  for (int i = 1; i <= n; i++)
    ancestral[i][0] = father[i];
  for (int j = 1; j < MAXL; j++)
    for (int i = 1; i <= n; i++)
      ancestral[i][j] = ancestral[ancestral[i][j - 1]][j - 1];
  int vv, uu;
  cin >> vv >> uu;
  cout << lca(vv, uu) << endl;
  return 0;
}
