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

int n, m;
vector<pii> edges;

struct dsu
{
  vector<pi> parent;
  vector<int> rank;
  vector<int> bipartite;

  dsu(int n)
  {
    parent.resize(n);
    rank.resize(n);
    bipartite.resize(n);
    for (int v = 0; v < n; v++)
    {
      parent[v] = {v, 0};
      rank[v] = 0;
      bipartite[v] = 1;
    }
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
dsu d;
bool solve(int l, int r)
{
  // dado um conjunto de n pares
  // saber se existem 2 pares (a, b) e (c, d)
  // tal que (a != c), (a != d), (b != c) e (b != d)
  vector<pi> pairs;
  for (int k = l; k < r; k++)
  {
    pi va = d.find_set(edges[k].sec.fir);
    pi vb = d.find_set(edges[k].sec.sec);
    if (va.fir == vb.fir && va.sec != vb.sec)
      continue;
    int a = (!va.sec) ? va.fir : 1e9 + va.fir;
    int b = (!vb.sec) ? vb.fir : 1e9 + vb.fir;
    if (a < b)
      swap(a, b);
    pairs.pb({a, b});
  }
  if (pairs.size() <= 1)
    return false;
  pi j = pairs.back();
  set<int> a, b;
  for (auto const &i : pairs)
  {
    if (i == j)
      continue;
    else if (i.fir == j.fir || i.sec == j.fir)
      (i.fir != j.fir) ? a.insert(i.fir) : a.insert(i.sec);
    else if (i.fir == j.sec || i.sec == j.sec)
      (i.fir != j.sec) ? b.insert(i.fir) : b.insert(i.sec);
    else
      return true;
  }
  if (!a.size() || !b.size())
    return false;
  return (a != b);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  d = dsu(n);
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    edges.pb({c, {a, b}});
  }
  sort(edges.rbegin(), edges.rend());
  int i = 0;
  bool is = true;
  vector<int> ans;
  while (i < m)
  {
    int j = i;
    while (j < m && edges[j].fir == edges[i].fir)
      j++;
    if (solve(i, j) && is)
      ans.pb(edges[i].fir);
    for (int k = i; k < j; k++)
    {
      d.add_edge(edges[k].sec.fir, edges[k].sec.sec);
      if (!d.is_bipartite(edges[k].sec.fir))
      {
        is = false;
        break;
      }
    }
    i = j;
  }
  if (is)
    ans.pb(0);
  if (!ans.size())
  {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  reverse(ans.begin(), ans.end());
  for (auto const &i : ans)
    cout << i << endl;
  return 0;
}