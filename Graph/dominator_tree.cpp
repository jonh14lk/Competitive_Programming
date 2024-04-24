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
#define MAXN 200005
#define mod 998244353

struct dominator_tree
{
  int n, t;
  vector<vector<int>> g, tree, rg, bucket;
  vector<int> dfs_l, dfs_r, idom, sdom, prv, pre, ancestor, label, preorder;

  dominator_tree(vector<vector<int>> &adj, int source)
  {
    int n = adj.size();
    g = adj;
    tree.resize(n);
    rg.resize(n);
    bucket.resize(n);
    dfs_l.resize(n);
    dfs_r.resize(n);
    idom.resize(n);
    sdom.assign(n, -1);
    prv.resize(n);
    pre.assign(n, -1);
    ancestor.assign(n, -1);
    label.resize(n);
    build(source);
  }
  void dfs(int v)
  {
    pre[v] = ++t;
    sdom[v] = label[v] = v;
    preorder.pb(v);
    for (auto const &nxt : g[v])
    {
      if (sdom[nxt] == -1)
      {
        prv[nxt] = v;
        dfs(nxt);
      }
      rg[nxt].pb(v);
    }
  }
  int eval(int v)
  {
    if (ancestor[v] == -1)
      return v;
    if (ancestor[ancestor[v]] == -1)
      return label[v];
    int u = eval(ancestor[v]);
    if (pre[sdom[u]] < pre[sdom[label[v]]])
      label[v] = u;
    ancestor[v] = ancestor[u];
    return label[v];
  }
  void dfs2(int v)
  {
    dfs_l[v] = t++;
    for (auto const &nxt : tree[v])
    {
      dfs2(nxt);
    }
    dfs_r[v] = t++;
  }
  void build(int s)
  {
    t = 0;
    dfs(s);
    if (preorder.size() == 1)
    {
      return;
    }
    int sz = preorder.size();
    for (int i = sz - 1; i >= 1; i--)
    {
      int w = preorder[i];
      for (auto const &v : rg[w])
      {
        int u = eval(v);
        if (pre[sdom[u]] < pre[sdom[w]])
          sdom[w] = sdom[u];
      }
      bucket[sdom[w]].push_back(w);
      ancestor[w] = prv[w];
      for (auto const &v : bucket[prv[w]])
      {
        int u = eval(v);
        idom[v] = (u == v) ? sdom[v] : u;
      }
      bucket[prv[w]].clear();
    }
    for (int i = 1; i < preorder.size(); i++)
    {
      int w = preorder[i];
      if (idom[w] != sdom[w])
        idom[w] = idom[idom[w]];
      tree[idom[w]].push_back(w);
    }
    idom[s] = sdom[s] = -1;
    t = 0;
    dfs2(s);
  }
  bool dominates(int u, int v)
  {
    if (pre[v] == -1)
      return 1;
    return dfs_l[u] <= dfs_l[v] && dfs_r[v] <= dfs_r[u];
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
  }
  dominator_tree d(adj, 0);
  vector<int> ans;
  for (int i = 0; i < n; i++)
  {
    if (d.dominates(i, n - 1))
      ans.pb(i);
  }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i] + 1 << " \n"[i == ans.size() - 1];
}
// https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
// https://cses.fi/problemset/task/1703/ (problema desse codigo)
// https://codeforces.com/gym/100513/problem/L
// https://codeforces.com/contest/757/problem/F

// dado um vertice source s
// dizemos que u domina w, se todos os caminhos de
// s ate w passam pelo vertice u

// dizemos que u é um dominador imediato de w se u domina w
// e todos os demais dominadores de w, dominam u

// 1 - todo vertice (tirando o source) tem um dominador
// pois o source domina todos os demais vertices

// 2 - todo vertice (tirando o source) tem exatamente um
// unico dominador imediato

// se eu crio um grafo com todas as arestas do tipo
// (dominador imediato de w) - w
// para todos os vertices w que nao sao a source
// esse grafo eh uma arvore
// e eh a dominator tree