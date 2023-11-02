#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define MAXN 100005

int n;
int par[MAXN];
vector<int> adj[MAXN];
set<pair<int, int>> m[MAXN];

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
  int binary_lifting(int u, int v)
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
    int at = binary_lifting(s, v);
    return (depth[s] + depth[v] - 2 * depth[at]);
  }
}

namespace cd
{
  int sz;
  vector<int> subtree_size;
  vector<bool> visited;

  void dfs(int s, int f)
  {
    sz++;
    subtree_size[s] = 1;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
      {
        dfs(v, s);
        subtree_size[s] += subtree_size[v];
      }
    }
  }
  int get_centroid(int s, int f)
  {
    bool is_centroid = true;
    int heaviest_child = -1;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
      {
        if (subtree_size[v] > sz / 2)
          is_centroid = false;
        if (heaviest_child == -1 || subtree_size[v] > subtree_size[heaviest_child])
          heaviest_child = v;
      }
    }
    return (is_centroid && sz - subtree_size[s] <= sz / 2) ? s : get_centroid(heaviest_child, s);
  }
  int decompose_tree(int s)
  {
    sz = 0;
    dfs(s, s);
    int centroid = get_centroid(s, s);
    visited[centroid] = true;
    for (auto const &v : adj[centroid])
    {
      if (!visited[v])
        par[decompose_tree(v)] = centroid;
    }
    return centroid;
  }
  void init()
  {
    subtree_size.resize(n);
    visited.resize(n);
    for (int i = 0; i < n; i++)
      par[i] = -1;
    decompose_tree(0);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  cd::init();
  lca::init();
  vector<int> ans;
  auto add = [&](int v)
  {
    int u = v;
    while (v != -1)
    {
      m[v].insert({lca::dist(u, v), u});
      v = par[v];
    }
  };
  auto qry = [&](int v)
  {
    if (v == n - 1)
    {
      ans.pb(v);
      return;
    }
    int u = v;
    pair<int, int> best = {1e9, 1e9};
    while (v != -1)
    {
      if (m[v].size() > 0)
      {
        pair<int, int> curr = *m[v].begin();
        curr.first += lca::dist(u, v);
        best = min(best, curr);
      }
      v = par[v];
    }
    ans.pb(best.second);
  };
  for (int v = n - 1; v >= 0; v--)
  {
    qry(v);
    add(v);
  }
  reverse(ans.begin(), ans.end());
  for (auto const &i : ans)
    cout << i + 1 << " ";
  cout << endl;
}