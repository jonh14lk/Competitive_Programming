// heavy-light decomposition
// https://www.hackerrank.com/challenges/heavy-light-white-falcon/problem
// You are given a tree with n nodes.
// The problem asks you to operate the following two types of queries:
// "1 a b" assign to b the value of the node a.
// "2 a b" print the maximum value of the nodes on the unique path between a and b.

#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 50000
#define MAXL 20
#define mod 1000000007

int n, q, cont;
vector<int> adj[MAXN];
int parent[MAXN];
int chain[MAXN];
int depth[MAXN];
int dfn[MAXN];
int maxx[2 * MAXN];

int dfs(int s, int father)
{
  int size = 1, maxat = 0;
  parent[s] = father;
  chain[s] = -1;
  for (int i = 0; i < adj[s].size(); i++)
  {
    if (adj[s][i] != father)
    {
      depth[adj[s][i]] = depth[s] + 1;
      int at = dfs(adj[s][i], s);
      size += at;
      if (at > maxat)
        maxat = at, chain[s] = adj[s][i];
    }
  }
  return size;
}
void hld(int u, int p, int top)
{
  dfn[u] = cont++;
  if (chain[u] >= 0)
  {
    hld(chain[u], u, top);
    for (int i = 0; i < adj[u].size(); i++)
      if (adj[u][i] != p && adj[u][i] != chain[u])
        hld(adj[u][i], u, adj[u][i]);
  }
  chain[u] = top;
}
void update(int a, int b)
{
  int i = dfn[a] + MAXN;
  maxx[i] = b;
  while (i >>= 1)
  {
    maxx[i] = max(maxx[2 * i], maxx[2 * i + 1]);
  }
}
int get_max(int l, int r)
{
  int ans = 0;
  for (l += MAXN, r += MAXN; l < r; l >>= 1, r >>= 1)
  {
    if (l & 1)
      ans = max(ans, maxx[l++]);
    if (r & 1)
      ans = max(ans, maxx[--r]);
  }
  return ans;
}
void query(int a, int b)
{
  int ans = 0;
  while (chain[a] != chain[b])
  {
    if (depth[chain[a]] > depth[chain[b]])
    {
      ans = max(ans, get_max(dfn[chain[a]], dfn[a] + 1));
      a = parent[chain[a]];
    }
    else
    {
      ans = max(ans, get_max(dfn[chain[b]], dfn[b] + 1));
      b = parent[chain[b]];
    }
  }
  if (depth[a] > depth[b])
    ans = max(ans, get_max(dfn[b], dfn[a] + 1));
  else
    ans = max(ans, get_max(dfn[a], dfn[b] + 1));
  cout << ans << endl;
}
signed main()
{
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  dfs(0, -1);
  hld(0, -1, 0);
  while (q--)
  {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1)
      update(a, b);
    else
      query(a, b);
  }
  return 0;
}
