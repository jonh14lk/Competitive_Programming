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
#define MAXN 301
#define mod 1000000007
#define INF 1e9

namespace mcf
{
  struct edge
  {
    int to, capacity, cost, res;
  };

  int source, destiny;
  vector<edge> adj[MAXN];
  vector<int> dist;
  vector<int> parent;
  vector<int> edge_index;
  vector<bool> in_queue;

  void add_edge(int a, int b, int c, int d)
  {
    adj[a].pb({b, c, d, (int)adj[b].size()});      // aresta normal
    adj[b].pb({a, 0, -d, (int)adj[a].size() - 1}); // aresta do grafo residual
  }
  bool dijkstra(int s) // rodando o dijkstra, terei o caminho de custo minimo
  {                    // que eu consigo passando pelas arestas que possuem capacidade > 0
    dist.assign(MAXN, INF);
    parent.assign(MAXN, -1);
    edge_index.assign(MAXN, -1);
    in_queue.assign(MAXN, false);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
      int u = q.front(), idx = 0;
      q.pop();
      in_queue[u] = false;
      for (auto const &v : adj[u])
      {
        if (v.capacity && dist[v.to] > dist[u] + v.cost)
        {
          dist[v.to] = dist[u] + v.cost;
          parent[v.to] = u;
          edge_index[v.to] = idx;
          if (!in_queue[v.to])
          {
            in_queue[v.to] = true;
            q.push(v.to);
          }
        }
        idx++;
      }
    }
    return dist[destiny] != INF; // se eu cheguei em destiny por esse caminho, ainda posso passar fluxo
  }
  int get_cost()
  {
    int flow = 0, cost = 0;
    while (dijkstra(source)) // rodo um dijkstra para saber qual o caminho que irei agora
    {
      int curr_flow = INF, curr = destiny;
      while (curr != source) // com isso, vou percorrendo o caminho encontrado para achar a aresta "gargalo"
      {
        int p = parent[curr];
        curr_flow = min(curr_flow, adj[p][edge_index[curr]].capacity);
        curr = p;
      }
      flow += curr_flow;                 // fluxo que eu posso passar por esse caminho = custo da aresta "gargalo"
      cost += curr_flow * dist[destiny]; // quanto eu gasto para passar esse fluxo no caminho encontrado
      curr = destiny;
      while (curr != source) // apos achar a aresta gargalo, passamos o fluxo pelo caminho encontrado
      {
        int p = parent[curr];
        int res_idx = adj[p][edge_index[curr]].res;
        adj[p][edge_index[curr]].capacity -= curr_flow;
        adj[curr][res_idx].capacity += curr_flow;
        curr = p;
      }
    }
    return cost; // ao final temos a resposta :)
  }
} // namespace mcf
signed main()
{
  int n;
  cin >> n;
  int v[n][n];
  mcf::source = 0, mcf::destiny = (2 * n) + 1;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> v[i][j];
      mcf::add_edge(i + 1, j + n + 1, 1, v[i][j]);
    }
  }
  for (int i = 1; i <= n; i++)
    mcf::add_edge(mcf::source, i, 1, 0);
  for (int i = n + 1; i <= n + n; i++)
    mcf::add_edge(i, mcf::destiny, 1, 0);
  cout << mcf::get_cost << endl;
}
