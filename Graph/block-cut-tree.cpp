#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

struct dsu
{
  vector<pi> parent;
  vector<int> rank;
  vector<int> bipartite;

  void reset(int v)
  {
    parent[v] = {v, 0};
    rank[v] = 0;
    bipartite[v] = 1;
  }
  dsu(int n)
  {
    parent.resize(n);
    rank.resize(n);
    bipartite.resize(n);
    for (int v = 0; v < n; v++)
      reset(v);
  }
  dsu() {}
  pi find_set(int v)
  {
    if (v != parent[v].fir)
    {
      int parity = parent[v].sec;
      parent[v] = find_set(parent[v].fir);
      parent[v].sec ^= parity;
    }
    return parent[v];
  }
  void add_edge(int a, int b)
  {
    pi pa = find_set(a);
    a = pa.fir;
    int x = pa.sec;
    pi pb = find_set(b);
    b = pb.fir;
    int y = pb.sec;
    if (a == b)
    {
      if (x == y)
        bipartite[a] = 0;
    }
    else
    {
      if (rank[a] < rank[b])
        swap(a, b);
      parent[b] = {a, x ^ y ^ 1};
      bipartite[a] &= bipartite[b];
      if (rank[a] == rank[b])
        rank[a]++;
    }
  }
  bool is_bipartite(int v)
  {
    return bipartite[find_set(v).fir];
  }
};
struct block_cut_tree
{
  // Source: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/blockCutTree.cpp
  // Cria a block-cut tree, uma arvore com os blocos
  // e os pontos de articulacao
  // Blocos sao componentes 2-vertice-conexos maximais
  // Uma 2-coloracao da arvore eh tal que uma cor sao
  // os blocos, e a outra cor sao os pontos de art.
  // Funciona para grafo nao conexo
  //
  // art[i] responde o numero de novas componentes conexas
  // criadas apos a remocao de i do grafo g
  // Se art[i] >= 1, i eh ponto de articulacao
  //
  // Para todo i <= blocks.size()
  // blocks[i] eh uma componente 2-vertce-conexa maximal
  // edgblocks[i] sao as arestas do bloco i
  // tree[i] eh um vertice da arvore que corresponde ao bloco i
  // tree - eh a propia block-cut tree
  // pos[i] responde a qual vertice da arvore vertice i pertence
  // Arvore tem no maximo 2n vertices
  //
  // O(n + m)
  vector<vector<int>> g, blocks, tree;
  vector<vector<pi>> edgblocks;
  stack<int> s;
  stack<pi> s2;
  vector<int> id, art, pos;

  block_cut_tree(vector<vector<int>> g_) : g(g_)
  {
    int n = g.size();
    id.resize(n, -1), art.resize(n), pos.resize(n);
    build();
  }
  int dfs(int i, int &t, int p = -1)
  {
    int lo = id[i] = t++;
    s.push(i);
    if (p != -1)
    {
      s2.emplace(i, p);
    }
    for (int j : g[i])
    {
      if (j != p and id[j] != -1)
        s2.emplace(i, j);
    }
    for (int j : g[i])
    {
      if (j != p)
      {
        if (id[j] == -1)
        {
          int val = dfs(j, t, i);
          lo = min(lo, val);
          if (val >= id[i])
          {
            art[i]++;
            blocks.emplace_back(1, i);
            while (blocks.back().back() != j)
            {
              blocks.back().pb(s.top());
              s.pop();
            }
            edgblocks.emplace_back(1, s2.top());
            s2.pop();
            pi aux = {j, i};
            while (edgblocks.back().back() != aux)
            {
              edgblocks.back().pb(s2.top());
              s2.pop();
            }
          }
          // if (val > id[i]) aresta i-j eh ponte
        }
        else
        {
          lo = min(lo, id[j]);
        }
      }
    }
    if (p == -1 and art[i])
    {
      art[i]--;
    }
    return lo;
  }
  void build()
  {
    int t = 0;
    for (int i = 0; i < g.size(); i++)
    {
      if (id[i] == -1)
        dfs(i, t, -1);
    }
    tree.resize(blocks.size());
    for (int i = 0; i < g.size(); i++)
    {
      if (art[i])
        pos[i] = tree.size(), tree.emplace_back();
    }
    for (int i = 0; i < blocks.size(); i++)
    {
      for (int j : blocks[i])
      {
        if (!art[j])
          pos[j] = i;
        else
          tree[i].pb(pos[j]), tree[pos[j]].pb(i);
      }
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  block_cut_tree bt(adj);
  vector<vector<int>> g(n);
  dsu d(n);
  for (auto const &v : bt.edgblocks)
  {
    vector<int> guys;
    for (auto const &j : v)
    {
      guys.pb(j.fir);
      guys.pb(j.sec);
      d.add_edge(j.fir, j.sec);
    }
    bool bip = 1;
    for (auto const &j : guys)
    {
      bip &= d.is_bipartite(j);
    }
    if (bip)
    {
      for (auto const &j : v)
      {
        g[j.fir].pb(j.sec);
        g[j.sec].pb(j.fir);
      }
    }
    for (auto const &j : guys)
    {
      d.reset(j);
    }
  }
  vector<bool> vis(n, 0);
  vector<bool> c(n, 0);
  int a = 0, b = 0;
  for (int i = 0; i < n; i++)
  {
    if (vis[i])
      continue;
    int x = 1, y = 0;
    queue<int> q;
    q.push(i);
    vis[i] = 1;
    while (!q.empty())
    {
      int k = q.front();
      q.pop();
      for (auto const &i : g[k])
      {
        if (!vis[i])
        {
          vis[i] = 1;
          c[i] = c[k] ^ 1;
          (c[i] == 1) ? y++ : x++;
          q.push(i);
        }
      }
    }
    a += (x * (x - 1)) / 2;
    a += (y * (y - 1)) / 2;
    b += (x * y);
  }
  cout << a << " " << b << endl;
  return 0;
}
// https://codeforces.com/gym/103934/problem/M
// pares (a, b) com a < b
// contar pares (a, b) tal que todos os caminhos de a para b possuem distancia impar
// contar pares (a, b) tal que todos os caminhos de a para b possuem distancia par

// grafo biconexo (ou 2-vertice-conexo) - nao tem ponto de articulação
// blocos - são subgrafos biconexos maximais (sem ponto de articulação)

// block graph
// grafo que tem um vertice para cada bloco do grafo G
// e uma aresta entre dois vértices tal que os blocos correspondentes tem um vértice em comum

// block-cut tree
// um ponto de articulação eh um vertice que está em dois ou mais blocos
// a estrutura dos blocos e dos pontos de articulação de um grafo conectado pode ser descrita por uma arvore chamada de árvore de block-cut tree
// essa arvore tem um vértice para cada bloco e para cada ponto de articulação do grafo dado.
// tem uma aresta na block-cut tree para cada par (bloco, ponto de articulação), tal que esse ponto de articulação tá no bloco

// para o problema:
// para um grafo nao bipartido que é biconexo, tem caminhos de tamanho impar e par entre qualquer par de vertices

// um caminho em um grafo G, tem meio que um caminho equivalente na sua block-cut tree
// da pra pensar em resolver para cada bloco

// resolvendo pra cada bloco:
// o bloco tem que ser bipartido
// quando o bloco nao eh bipartido, eu nao considero as arestas dele

// considerando o grafo restante sendo bipartido
// da pra resolver pra cada componente conexa
// caminhos entre vertices de mesma cor tem paridade impar
// caminhos entre vertices de cor diferente tem paridade par

// https://codeforces.com/gym/102512/problem/A
// ter queries do tipo 
// quantos pontos de articulação desconectam u e v
// dai monta a block cut tree
// para cada ponto de articulação, seta a pos[i] dele como 1 na arvore
// e o valor dos demais vértices como 0
// dai responde uma query com hld (ou com lca tbm sai)
