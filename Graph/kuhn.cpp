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
#define MAXN 2001
#define mod 998244353

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct kuhn
{
  int n, m, at;
  vector<vector<int>> g;
  vector<int> vis, ma, mb;

  kuhn(int n_, int m_) : n(n_), m(m_), at(0), g(n),
                         vis(n), ma(n, -1), mb(m, -1) {}
  void add_edge(int a, int b) { g[a].push_back(b); }
  bool dfs(int i)
  {
    vis[i] = at;
    for (int j : g[i])
    {
      if (mb[j] == -1)
      {
        ma[i] = j, mb[j] = i;
        return true;
      }
    }
    for (int j : g[i])
    {
      if (vis[mb[j]] != at && dfs(mb[j]))
      {
        ma[i] = j, mb[j] = i;
        return true;
      }
    }
    return false;
  }
  int augment(int i) // pode usar quando tou adicionando o vertice i pela primeira vez no grafo
  {
    shuffle(g[i].begin(), g[i].end(), rng);
    if (dfs(i))
      at++;
    return at;
  }
  int matching() // calcula o max matching
  {
    int aum = 1;
    while (aum)
    {
      for (auto &i : g)
        shuffle(i.begin(), i.end(), rng);
      for (int j = 0; j < n; j++)
        vis[j] = 0;
      aum = 0;
      for (int i = 0; i < n; i++)
        if (ma[i] == -1 and dfs(i))
          at++, aum = 1;
    }
    return at;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<int> p(n);
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
  }
  vector<int> c(n);
  vector<vector<pi>> v(5001);
  for (int i = 0; i < n; i++)
  {
    cin >> c[i];
    c[i]--;
    v[p[i]].pb({i, c[i]});
  }
  int q;
  cin >> q;
  vector<int> qry(q);
  vector<bool> rem(n, 0);
  for (int i = 0; i < q; i++)
  {
    cin >> qry[i];
    qry[i]--;
    rem[qry[i]] = 1;
  }
  int sz = m + 1;
  kuhn h(5001, sz);
  vector<int> ans(q);
  int mex = 0;
  for (auto const &j : v[0])
  {
    if (!rem[j.fir])
      h.add_edge(0, j.sec);
  }
  h.augment(0);
  for (int i = q - 1; i >= 0; i--)
  {
    int x = qry[i];
    while (mex < m && h.at == mex + 1)
    {
      mex++;
      for (auto const &j : v[mex])
      {
        if (!rem[j.fir])
          h.add_edge(mex, j.sec);
      }
      h.augment(mex);
    }
    ans[i] = mex;
    rem[x] = 0;
    if (p[x] <= mex)
    {
      h.add_edge(p[x], c[x]);
      h.matching();
    }
  }
  for (auto const &i : ans)
    cout << i << endl;
  return 0;
}
// problema de matching incremental, ir adicionando arestas e calculando o max matching
// https://codeforces.com/contest/1139/problem/E

// selecionar um student de cada club, caso o club possua pelo menos um caba
// pros selecionados, maximizar o mex

// fazer as queries ao contrario talvez seja o caminho