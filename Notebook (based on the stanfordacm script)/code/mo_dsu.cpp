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
#define MAXN 50001
#define mod 1000000007

const int block = 224;

struct query
{
  int l, r, i;
};

vector<query> queries[block];

namespace dsu
{
  struct rollback
  {
    int u, v, ranku, rankv;
  };

  int num_sets;
  int parent[MAXN];
  int rank[MAXN];
  stack<rollback> op;

  int Find(int i)
  {
    return (parent[i] == i) ? i : Find(parent[i]);
  }
  bool Union(int x, int y, bool can_rollback)
  {
    int xx = Find(x);
    int yy = Find(y);
    if (xx != yy)
    {
      num_sets--;
      if (rank[xx] > rank[yy])
        swap(xx, yy);
      if (can_rollback)
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
  void rollback_all()
  {
    while (!op.empty())
      do_rollback();
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
} // namespace dsu
bool cmp(query a, query b)
{
  return a.r < b.r;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<pi> edges(m);
  for (int i = 0; i < m; i++)
  {
    cin >> edges[i].fir >> edges[i].sec;
    edges[i].fir--;
    edges[i].sec--;
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int l, r;
    cin >> l >> r;
    l--, r--;
    queries[l / block].pb({l, r, i});
  }
  for (int i = 0; i < block; i++)
  {
    if (queries[i].size())
      sort(queries[i].begin(), queries[i].end(), cmp);
  }
  vector<int> ans(q);
  for (int i = 0; i < block; i++)
  {
    if (!queries[i].size())
      continue;
    dsu::init(n);
    int limit = (i + 1) * block;
    for (auto const &j : queries[i])
    {
      while (j.r >= limit)
        dsu::Union(edges[limit].fir, edges[limit].sec, false), limit++;
      for (int k = j.l; k <= min(((i + 1) * block) - 1, j.r); k++)
        dsu::Union(edges[k].fir, edges[k].sec, true);
      ans[j.i] = dsu::num_sets;
      dsu::rollback_all();
    }
  }
  for (auto const &i : ans)
    cout << i << endl;
  return 0;
}
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/B
// temos que fazer algo parecido com um mo algorithm
// sendo que a operacao eh um union/rollback do dsu
// podemos aplicar a seguinte ideia:
// - separamos os queries em blocos (pelo l) de tamanho sqrt(n)
// - para cada bloco, ordenamos esse bloco em ordem crescente do r
// - com isso, em cada query eu posso fazer:
// - de l ate (limite daquele bloco) - 1, adiciono na marra, podendo dar rollback
// - como o r eh crescente, para os valores de r que forem maior do que o limit daquele block
// - eu ja posso deixar adicionado para sempre sem precisar dar rollback
// fica algo que funciona em coisas que voce pode dar rollback