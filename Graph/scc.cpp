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
#define MAXN 500005
#define mod 1000000007

int n, m;

bool vis[MAXN];
int root[MAXN];
vector<int> order;
vector<int> roots;
vector<int> comp;
vector<vector<int>> comps;
vector<int> adj[MAXN];
vector<int> adj_rev[MAXN];
vector<int> adj_scc[MAXN];

void dfs(int v)
{
  vis[v] = true;
  for (auto const &u : adj[v])
    if (!vis[u])
      dfs(u);
  order.pb(v);
}
void dfs2(int v)
{
  comp.pb(v);
  vis[v] = true;
  for (auto const &u : adj_rev[v])
    if (!vis[u])
      dfs2(u);
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
    adj_rev[b].pb(a);
  }
  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i);
  }
  reverse(order.begin(), order.end());
  memset(vis, false, sizeof(vis));
  for (auto const &v : order)
  {
    if (!vis[v])
    {
      comp.clear();
      dfs2(v);
      comps.pb(comp);
      // making condensation graph
      /*
      int r = comp.back();
      for (auto const &u : comp)
        root[u] = r;
      roots.push_back(r);
      */
    }
  }
  // making condensation graph
  /*
  for (int v = 0; v < n; v++)
  {
    for (auto const &u : adj[v])
    {
      int root_v = roots[v];
      int root_u = roots[u];
      if (root_u != root_v)
        adj_scc[root_v].pb(root_u);
    }
  }
  */
  // printing scc
  cout << comps.size() << endl;
  for (auto const &comp : comps)
  {
    cout << comp.size() << " ";
    for (auto const &u : comp)
      cout << u << " ";
    cout << endl;
  }
  return 0;
}
// to test: https://judge.yosupo.jp/problem/scc