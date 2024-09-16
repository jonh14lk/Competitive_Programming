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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 1000000007

int n, m, k;
set<int> all;
vector<int> path;
vector<pi> adj[MAXN];
set<pi> a[MAXN];
int color[MAXN];
bool vis[MAXN];
int deg[MAXN];
vector<int> ids[MAXN][MAXN];

void dfs(int s)
{
  while (a[s].size() > 0)
  {
    auto v = (*a[s].begin());
    a[s].erase(v);
    a[v.fir].erase({s, v.sec});
    dfs(v.fir);
  }
  path.pb(s);
}
void check(int i)
{
  vis[i] = 1;
  for (auto const &j : adj[i])
  {
    all.insert(j.sec);
    if (!vis[j.fir])
      check(j.fir);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
  vector<pi> hue;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b >> color[i];
    a--, b--;
    hue.pb({a, b});
    adj[a].pb({b, i});
    adj[b].pb({a, i});
    deg[a] ^= 1;
    deg[b] ^= 1;
    ids[a][b].pb(i);
    ids[b][a].pb(i);
  }
  // ciclo euleriano
  for (int i = 0; i < n; i++)
  {
    if (deg[i])
    {
      cout << "-1\n";
      exit(0);
    }
  }
  // checar se todas as arestas tao na mesma componente conexa
  int ini;
  for (int i = 0; i < n; i++)
  {
    if (adj[i].size() > 0)
      ini = i;
  }
  check(ini);
  if (all.size() < m)
  {
    cout << "-1\n";
    exit(0);
  }
  for (int j = 0; j < n; j++)
  {
    for (auto const &k : adj[j])
      a[j].insert(k);
  }
  dfs(ini);
  vector<int> edges;
  {
    int prv = -1;
    for (auto const &j : path)
    {
      if (prv != -1)
      {
        edges.pb(ids[j][prv].back());
        ids[j][prv].pop_back();
        ids[prv][j].pop_back();
      }
      prv = j;
    }
  }
  auto get_ot = [&](int i, int edge_idx)
  {
    if (hue[edge_idx].fir == i)
      return hue[edge_idx].sec;
    return hue[edge_idx].fir;
  };
  auto get_begin = [&]()
  {
    for (auto val : {hue[edges[0]].fir, hue[edges[0]].sec})
    {
      int at = val;
      bool ok = 1;
      for (int i = 0; i < edges.size(); i++)
      {
        if (at != hue[edges[i]].fir && at != hue[edges[i]].sec)
          ok = 0;
        at = get_ot(at, edges[i]);
      }
      ok &= (at == val);
      if (ok)
        return val;
    }
    return (int)-1;
  };
  for (int ii = 0, swaps = 0; ii < edges.size() && swaps < edges.size(); ii++)
  {
    ini = get_begin();
    for (int i = 0; i < edges.size(); i++)
    {
      int nxt = (i + 1) % edges.size();
      if (color[edges[i]] == color[edges[nxt]])
      {
        swaps++;
        int at = get_ot(ini, edges[i]);
        int at2 = at;
        int id = -1;
        for (int k = nxt; k != i; k = (k + 1) % edges.size())
        {
          at2 = get_ot(at2, edges[k]);
          if (at2 == at && color[edges[i]] != color[edges[k]] && color[edges[(k + 1) % edges.size()]] != color[edges[nxt]])
          {
            vector<int> vec;
            int l = nxt;
            while (1)
            {
              vec.pb(edges[l]);
              if (l == k)
                break;
              l = (l + 1) % edges.size();
            }
            l = nxt;
            while (1)
            {
              edges[l] = vec.back();
              vec.pop_back();
              if (l == k)
                break;
              l = (l + 1) % edges.size();
            }
            break;
          }
        }
      }
      ini = get_ot(ini, edges[i]);
    }
  }
  if (color[edges.front()] == color[edges.back()])
  {
    cout << "-1\n";
    exit(0);
  }
  for (int i = 1; i < edges.size(); i++)
  {
    if (color[edges[i]] == color[edges[i - 1]])
    {
      cout << "-1\n";
      exit(0);
    }
  }
  cout << get_begin() + 1 << endl;
  for (auto const &i : edges)
  {
    cout << i + 1 << " ";
  }
  cout << endl;
}
// se eu tenho um ciclo euleriano que eh
// A b c A d e f A
// eu posso trocar pra ser
// A b c A f e d A
// ou A d e f A c b A
// e assim por diante
// mas eu tenho que comecar por um vertice que tem duas arestas de cores distintas
// e duas arestas seguidas precisam ser de cores diferentes