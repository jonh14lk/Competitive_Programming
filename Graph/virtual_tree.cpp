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
#define pci pair<char, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

int n, ans;
vector<int> adj[MAXN];
vector<int> with_color[MAXN];
vector<pi> virt[MAXN];
int a[MAXN];
int dp[MAXN];
int dp2[MAXN];
int pot[MAXN];

namespace lca
{
  int l, timer;
  vector<int> tin, tout, depth;
  vector<vector<int>> up;

  void dfs(int v, int p)
  {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; i++)
      up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto const &u : adj[v])
    {
      if (p == u)
        continue;
      depth[u] = depth[v] + 1;
      dfs(u, v);
    }
    tout[v] = ++timer;
  }
  bool is_ancestor(int u, int v)
  {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
  int find_lca(int u, int v)
  {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;
    for (int i = l; i >= 0; i--)
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    return up[u][0];
  }
  void init()
  {
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(0, 0);
  }
  int dist(int s, int v)
  {
    int at = find_lca(s, v);
    return (depth[s] + depth[v] - 2 * depth[at]);
  }
}

// dp naive (fazer O(n) para cada cor)
// fixa uma cor c e faz uma dp on tree pra calcular
// quantas subtrees tem tal que todas as folhas sao da cor c
// e chamando o dfs saindo de qualquer vertice
// void dfs(int s, int p, int c)
// {
//   // dado que eu calculo o dp2[i] para cada filho
//   // para cada possivel subset (i1, i2, ..., ik) nao vazio de filhos
//   // acha o valor de dp2[i1] * dp2[i2] * ... * dp2[ik]
//   // no final eu quero a soma de todos esses valores, isso vai tar nessa variavel prod
//   int prod = 1;
//   for (auto const &i : adj[s])
//   {
//     if (i != p)
//     {
//       dfs(i, s, c);
//       prod = (prod * (dp2[i] + 1)) % mod;
//     }
//   }
//   prod = (prod - 1 + mod) % mod;
//   dp[s] = prod;
//   dp2[s] = prod;
//   if (a[s] == c)
//   {
//     dp[s] = (dp[s] + 1) % mod;
//     dp2[s] = (dp2[s] + 1) % mod;
//   }
//   for (auto const &i : adj[s])
//   {
//     if (i == p)
//       continue;
//     if (a[s] != c)
//       dp[s] = (dp[s] - dp2[i] + mod) % mod;
//   }
// }

// virtual tree
// dado um conjunto de vertices v
// montar uma arvore comprimida
// tal que escolhendo dois vertices do conjunto v[i] e v[j]
// lca(v[i], v[j]) também tá na arvore
// se o conjunto v tem k vertices
// entao a arvore comprimida tem menos do que 2k vertices
// O(k log(k)), sem considerar a complexidade de achar lca
int build_virt(vector<int> v)
{
  auto cmp = [&](int i, int j)
  {
    return lca::tin[i] < lca::tin[j];
  };
  sort(v.begin(), v.end(), cmp);
  for (int i = v.size() - 1; i > 0; i--)
  {
    v.pb(lca::find_lca(v[i], v[i - 1]));
  }
  sort(v.begin(), v.end(), cmp);
  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < v.size(); i++)
  {
    virt[v[i]].clear();
  }
  for (int i = 1; i < v.size(); i++)
  {
    virt[lca::find_lca(v[i - 1], v[i])].clear();
  }
  for (int i = 1; i < v.size(); i++)
  {
    int parent = lca::find_lca(v[i - 1], v[i]);
    int d = lca::dist(parent, v[i]);
    virt[parent].pb({v[i], d});
  }
  return v[0];
}
void dfs(int s, int c) // dp naive, so que fazer isso na virtual tree
{
  int prod = 1;
  for (auto const &i : virt[s])
  {
    dfs(i.fir, c);
    prod = (prod * (dp2[i.fir] + 1)) % mod;
  }
  prod = (prod - 1 + mod) % mod;
  dp[s] = prod;
  dp2[s] = prod;
  if (a[s] == c)
  {
    dp[s] = (dp[s] + 1) % mod;
    dp2[s] = (dp2[s] + 1) % mod;
  }
  for (auto const &i : virt[s])
  {
    if (a[s] != c)
      dp[s] = (dp[s] - dp2[i.fir] + mod) % mod;
  }
  ans = (ans + dp[s]) % mod;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  pot[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    pot[i] = (pot[i - 1] * 2) % mod;
  }
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    with_color[a[i]].pb(i);
  }
  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  lca::init();
  for (int i = 1; i <= n; i++)
  {
    if (with_color[i].size() > 0)
    {
      int root = build_virt(with_color[i]);
      dfs(root, i);
    }
  }
  cout << ans << endl;
}
// https://atcoder.jp/contests/abc340/tasks/abc340_g
// problema legal
// dado uma arvore com n vertices (n <= 2 * 10^5)
// cada vertice tem uma cor a[i]
// conte quantas subarvores existem tal que:
// todas as folhas nessa subarvore tem a mesma cor

// sei codar em O(n^2), rodando um dfs pra cada cor
// dai montar a virtual tree para cada cor
// e rodar a dp naive na virtual tree

// tambem resolve o https://codeforces.com/gym/103960/problem/L da sub de 2022