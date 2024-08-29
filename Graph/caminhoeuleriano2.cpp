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
#define mod 998244353

int deg[MAXN];
bool vis[MAXN];
vector<int> path;
vector<pi> edges, edges2;
vector<pi> ans;
vector<pi> adj[MAXN];
set<pi> a[MAXN];

void dfs2(int s)
{
  while (a[s].size() > 0)
  {
    auto v = (*a[s].begin());
    a[s].erase(v);
    a[v.fir].erase({s, v.sec});
    dfs2(v.fir);
  }
  path.pb(s);
}
void dfs(int i)
{
  vis[i] = 1;
  for (auto const &j : adj[i])
  {
    if (!vis[j.fir])
    {
      dfs(j.fir);
      if (deg[j.fir])
      {
        ans.pb(edges[j.sec]);
        deg[j.fir] ^= 1;
        deg[i] ^= 1;
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n, m;
    cin >> n >> m;
    edges.clear();
    edges2.clear();
    ans.clear();
    for (int i = 0; i < n; i++)
    {
      adj[i].clear();
      vis[i] = 0;
      deg[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
      int a, b, c;
      cin >> a >> b >> c;
      a--, b--;
      if (c == 1) // edges obrigatorios
      {
        edges2.pb({a, b});
        deg[a] ^= 1;
        deg[b] ^= 1;
      }
      else // edges nao obrigatorios
      {
        edges.pb({a, b});
        adj[a].pb({b, edges.size() - 1});
        adj[b].pb({a, edges.size() - 1});
      }
    }
    for (int i = 0; i < n; i++)
    {
      if (!vis[i])
        dfs(i);
    }
    bool ok = 1;
    for (int i = 0; i < n; i++)
    {
      if (deg[i])
        ok = 0;
    }
    if (!ok)
    {
      cout << "NO\n";
      continue;
    }
    for (int i = 0; i < n; i++)
    {
      a[i].clear();
    }
    // monta o grafo final e acha o ciclo euleriano
    // funciona para grafos com self loops e multiple edges
    int id = 0;
    for (auto [u, v] : ans)
    {
      a[u].insert({v, id});
      a[v].insert({u, id});
      id++;
    }
    for (auto [u, v] : edges2)
    {
      a[u].insert({v, id});
      a[v].insert({u, id});
      id++;
    }
    path.clear();
    dfs2(0);
    cout << "YES\n";
    cout << path.size() - 1 << endl;
    for (int i = 0; i < path.size(); i++)
      cout << path[i] + 1 << " ";
    cout << endl;
  }
  return 0;
}
// https://codeforces.com/contest/1994/problem/F
// dado um grafo, tem edges que sao obrigatorios de manter
// e outros q posso remover
// quero fazer com que um grafo tenha um ciclo euleriano
// no qual o grau de cada vertice eh par
// se tiver solucao, eu quero imprimir o ciclo euleriano