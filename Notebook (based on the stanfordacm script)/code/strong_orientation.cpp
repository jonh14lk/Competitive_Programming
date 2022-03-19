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
#define MAXN 1000005
#define mod 1000000007

int n, m, timer, comps, bridges;
vector<pi> edges;
vector<pi> adj[MAXN];
int tin[MAXN];
int low[MAXN];
bool vis[MAXN];
char orient[MAXN];

void find_bridges(int v)
{
  low[v] = timer, tin[v] = timer++;
  for (auto const &p : adj[v])
  {
    if (vis[p.sec])
      continue;
    vis[p.sec] = true;
    orient[p.sec] = (v == edges[p.sec].first) ? '>' : '<';
    if (tin[p.fir] == -1)
    {
      find_bridges(p.fir);
      low[v] = min(low[v], low[p.fir]);
      if (low[p.fir] > tin[v])
        bridges++;
    }
    else
    {
      low[v] = min(low[v], low[p.fir]);
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
    a--, b--;
    edges.pb({a, b});
    adj[a].pb({b, i});
    adj[b].pb({a, i});
  }
  memset(tin, -1, sizeof(tin));
  memset(low, -1, sizeof(low));
  for (int v = 0; v < n; v++)
  {
    if (tin[v] == -1)
    {
      comps++;
      find_bridges(v);
    }
  }
  // numero minimo de scc = numero de componentes + numero de pontes
  cout << comps + bridges << endl;
  // > - a aresta foi orientada da esquerda pra direita
  // < - a aresta foi orientada da direita pra esquerda
  for (int i = 0; i < m; i++)
    cout << orient[i];
  cout << endl;
  return 0;
}
// to_test: https://szkopul.edu.pl/problemset/problem/nldsb4EW1YuZykBlf4lcZL1Y/site/?key=statement
// strong orientation:
// encontrar uma orientacao para as arestas tal que o numero
// minimo de scc e o menor possivel