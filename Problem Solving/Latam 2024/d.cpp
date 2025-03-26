#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define MAXN 300005
#define pi pair<int, int>
#define fir first
#define sec second

vector<int> adj[MAXN];

struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;
  vector<vector<int>> comp;
  vector<int> ans;
  vector<int> acc;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    comp.resize(n);
    ans.assign(n, 0);
    acc.assign(n, 0);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
      comp[i].pb(i);
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  void make_set(int x, int y, int cost)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      acc[y] += (cost * sz[x]);
      for (auto const &i : comp[x])
      {
        comp[y].pb(i);
        ans[i] -= acc[y];
        ans[i] += acc[x];
        ans[i] += (cost * sz[y]);
      }
      parent[x] = y;
      sz[y] += sz[x];
      comp[x].clear();
      acc[x] = 0;
      tot--;
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  vector<pi> dale(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    dale[i] = {v[i], i};
  }
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  sort(dale.begin(), dale.end());
  vector<bool> vis(n, 0);
  dsu d(n);
  for (auto [c, x] : dale)
  {
    vis[x] = 1;
    for (auto const &y : adj[x])
    {
      if (vis[y] && (d.find_set(x) != d.find_set(y)))
        d.make_set(x, y, c);
    }
  }
  for (int i = 0; i < n; i++)
    cout << d.ans[i] + d.acc[d.find_set(i)] + v[i] << " ";
  cout << endl;
  return 0;
}