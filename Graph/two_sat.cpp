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
#define MAXN 200005
#define mod 1000000007

struct two_sat
{
  int n;
  vector<vector<int>> g, gr;  // gr is the reversed graph
  vector<int> comp, ord, ans; // comp[v]: ID of the SCC containing node v
  vector<bool> vis;

  two_sat() {}
  two_sat(int sz)
  {
    n = sz;
    g.assign(2 * n, vector<int>());
    gr.assign(2 * n, vector<int>());
    comp.resize(2 * n);
    vis.resize(2 * n);
    ans.resize(2 * n);
  }
  void add_edge(int u, int v)
  {
    g[u].push_back(v);
    gr[v].push_back(u);
  }
  // int x, bool val: if 'val' is true, we take the variable to be x. Otherwise we take it to be x's complement (not x).
  void implies(int i, bool f, int j, bool g) // a -> b
  {
    add_edge(i + (f ? 0 : n), j + (g ? 0 : n));
    add_edge(j + (g ? n : 0), i + (f ? n : 0));
  }
  void add_clause_or(int i, bool f, int j, bool g) // At least one of them is true
  {
    add_edge(i + (f ? n : 0), j + (g ? 0 : n));
    add_edge(j + (g ? n : 0), i + (f ? 0 : n));
  }
  void add_clause_xor(int i, bool f, int j, bool g) // only one of them is true
  {
    add_clause_or(i, f, j, g);
    add_clause_or(i, !f, j, !g);
  }
  void add_clause_and(int i, bool f, int j, bool g) // both of them have the same value
  {
    add_clause_xor(i, !f, j, g);
  }
  void set(int i, bool f) // Set a variable
  {
    add_clause_or(i, f, i, f);
  }
  void top_sort(int u)
  {
    vis[u] = 1;
    for (auto const &v : g[u])
    {
      if (!vis[v])
        top_sort(v);
    }
    ord.push_back(u);
  }
  void scc(int u, int id)
  {
    vis[u] = 1;
    comp[u] = id;
    for (auto const &v : gr[u])
    {
      if (!vis[v])
        scc(v, id);
    }
  }
  bool solve()
  {
    fill(vis.begin(), vis.end(), 0);
    for (int i = 0; i < 2 * n; i++)
    {
      if (!vis[i])
        top_sort(i);
    }
    fill(vis.begin(), vis.end(), 0);
    reverse(ord.begin(), ord.end());
    int id = 0;
    for (const auto &v : ord)
    {
      if (!vis[v])
        scc(v, id++);
    }
    for (int i = 0; i < n; i++)
    {
      if (comp[i] == comp[i + n])
        return 0;
      ans[i] = (comp[i] > comp[i + n]) ? 1 : 0;
    }
    return 1;
  }
};
signed main()
{
}
//  https://codeforces.com/blog/entry/92977
//  https://codeforces.com/blog/entry/16205
//  https://cp-algorithms.com/graph/2SAT.html