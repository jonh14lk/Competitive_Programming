#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 5005
#define mod 998244353

struct lca
{
  int n;
  vector<vector<int>> adj;
  vector<int> vec;
  int l, timer;
  vector<int> tin, tout, depth;
  vector<vector<pi>> up;

  void dfs(int v, int p)
  {
    tin[v] = ++timer;
    up[v][0] = {p, min(vec[v], vec[p])};
    for (int i = 1; i <= l; i++)
    {
      up[v][i].fir = up[up[v][i - 1].fir][i - 1].fir;
      up[v][i].sec = min(up[v][i - 1].sec, up[up[v][i - 1].fir][i - 1].sec);
    }
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
      if (!is_ancestor(up[u][i].fir, v))
        u = up[u][i].fir;
    return up[u][0].fir;
  }
  int dist(int s, int v)
  {
    int at = find_lca(s, v);
    return (depth[s] + depth[v] - 2 * depth[at]);
  }
  int solve(int u, int d)
  {
    int ans = vec[u];
    for (int i = l; i >= 0; i--)
    {
      if (d & (1 << i))
      {
        ans = min(ans, up[u][i].sec);
        u = up[u][i].fir;
      }
    }
    return ans;
  }
  int rmq(int u, int v)
  {
    int l = find_lca(u, v);
    return min(solve(u, dist(u, l)), solve(v, dist(v, l)));
  }
  lca(vector<vector<int>> &_adj, vector<int> &_vec)
  {
    adj = _adj;
    vec = _vec;
    n = adj.size();
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<pi>(l + 1));
    dfs(0, 0);
  }
};
signed main()
{
}
// valores nos vertices
// rmq considerando o caminho entre os vertices u e v