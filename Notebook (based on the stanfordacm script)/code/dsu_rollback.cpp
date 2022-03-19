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
#define MAXN 600005
#define mod 1000000007

namespace dsu
{
  struct rollback
  {
    int u, v, rankv, ranku;
  };

  int num_sets;
  int parent[MAXN];
  int rank[MAXN];
  stack<rollback> op;

  int Find(int i)
  {
    return (parent[i] == i) ? i : Find(parent[i]);
  }
  bool Union(int x, int y)
  {
    int xx = Find(x);
    int yy = Find(y);
    if (xx != yy)
    {
      num_sets--;
      if (rank[xx] > rank[yy])
        swap(xx, yy);
      op.push({xx, yy, rank[xx], rank[yy]});
      parent[xx] = yy;
      if (rank[xx] == rank[yy])
        rank[yy]++;
      return true;
    }
    return false;
  }
  void do_rollback()
  {
    if (op.empty())
      return;
    rollback x = op.top();
    op.pop();
    num_sets++;
    parent[x.v] = x.v;
    rank[x.v] = x.rankv;
    parent[x.u] = x.u;
    rank[x.u] = x.ranku;
  }
  void init(int n)
  {
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      rank[i] = 0;
    }
    num_sets = n;
  }
}
namespace seg
{
  struct query
  {
    int v, u, is_bridge;
  };

  vector<vector<query>> t(4 * MAXN);
  int ans[MAXN];

  void add(int i, int l, int r, int ql, int qr, query q)
  {
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      t[i].push_back(q);
      return;
    }
    int mid = (l + r) >> 1;
    add((i << 1), l, mid, ql, qr, q);
    add((i << 1) | 1, mid + 1, r, ql, qr, q);
  }
  void dfs(int i, int l, int r)
  {
    for (query &q : t[i])
      if (dsu::Union(q.v, q.u))
        q.is_bridge = 1;
    if (l == r)
      ans[l] = dsu::num_sets;
    else
    {
      int mid = (l + r) >> 1;
      dfs((i << 1), l, mid);
      dfs((i << 1) | 1, mid + 1, r);
    }
    for (query q : t[i])
      if (q.is_bridge)
        dsu::do_rollback();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  int time = 0;
  map<pi, int> tin;
  vector<int> queries;
  while (q--)
  {
    char t;
    cin >> t;
    if (t == '?')
    {
      queries.pb(++time);
    }
    else if (t == '+')
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      if (a > b)
        swap(a, b);
      tin[{a, b}] = ++time;
    }
    else
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      if (a > b)
        swap(a, b);
      seg::query kappa = {a, b, 0};
      seg::add(1, 0, MAXN - 1, tin[{a, b}], ++time, kappa);
      tin[{a, b}] = -1;
    }
  }
  for (auto const &i : tin)
  {
    if (i.sec != -1)
    {
      seg::query kappa = {i.fir.fir, i.fir.sec, 0};
      seg::add(1, 0, MAXN - 1, i.sec, ++time, kappa);
    }
  }
  dsu::init(n);
  seg::dfs(1, 0, MAXN - 1);
  for (auto const &i : queries)
    cout << seg::ans[i] << endl;
  return 0;
}
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C
// conectividade dinamica
// para uma query (u, v)
// podemos descrever em um intervalo [l, r]
// l = quando a aresta (u, v) foi adicionada
// r = quando a aresta (u, v) foi removida
// dai agora que temos um intervalo, podemos adicionar
// a query (u, v) em uma segtree "adaptada"
// no final rodamos um dfs nessa segtree e vamos atualizando as repostas das queries
// quando estamos em uma posicao na seg, dou union em todos os caras daquela posicao
// e em seguida chamo pros meus filhos, quando chego em uma folha, ela eh equivalente
// a uma unidade de "tempo", logo a resposta para aquele tempo eh a resposta atual no dsu
// e ao sair recursivamente, vou dando rollbacks no dsu
