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
#define MAXN 501
#define mod 1000000007

int curr_hash = 1;
map<vector<int>, int> mp;

struct hash_tree
{
  pi h;
  int n;
  vector<int> c, sz, large_comp;
  vector<vector<int>> adj;

  hash_tree(vector<vector<int>> &a)
  {
    n = a.size();
    adj = a;
  }
  void dfs(int s, int p)
  {
    sz[s] = 1;
    large_comp[s] = 0;
    for (auto const &v : adj[s])
    {
      if (v != p)
      {
        dfs(v, s);
        sz[s] += sz[v];
        large_comp[s] = max(large_comp[s], sz[v]);
      }
    }
    large_comp[s] = max(large_comp[s], n - sz[s]);
  }
  int dfs2(int s, int p)
  {
    if (s == -1)
      return -1;
    vector<int> child;
    for (auto const &v : adj[s])
    {
      if (v != p)
        child.pb(dfs2(v, s));
    }
    sort(child.begin(), child.end());
    if (!mp[child])
      mp[child] = curr_hash++;
    return mp[child];
  }
  pi get_hash()
  {
    sz.assign(n, 0);
    large_comp.assign(n, 0);
    dfs(0, -1);
    int best = 1e18;
    for (int i = 0; i < n; i++)
    {
      if (large_comp[i] < best)
      {
        best = large_comp[i];
        c.clear();
      }
      if (large_comp[i] == best)
        c.pb(i);
    }
    while (c.size() < 2)
      c.pb(-1);
    h.fir = dfs2(c[0], -1);
    h.sec = dfs2(c[1], -1);
    if (h.fir > h.sec)
      swap(h.fir, h.sec);
    return h;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    vector<vector<int>> b(n);
    for (int i = 0; i < n - 1; i++)
    {
      int x, y;
      cin >> x >> y;
      x--, y--;
      a[x].pb(y);
      a[y].pb(x);
    }
    for (int i = 0; i < n - 1; i++)
    {
      int x, y;
      cin >> x >> y;
      x--, y--;
      b[x].pb(y);
      b[y].pb(x);
    }
    (hash_tree(a).get_hash() == hash_tree(b).get_hash()) ? cout << "YES\n" : cout << "NO\n";
  }
  return 0;
}
// https://www.spoj.com/problems/TREEISO/
// https://www.beecrowd.com.br/judge/en/problems/view/1229
// hash de arvores
// para descobrir se duas arvores sao isomorfas

// 1 - achar todos os centroides da arvore (toda arvore tem no maximo 2 centroides)
// 2 - achar o hashing com a arvore enraizada em cada centroid
// 3 - dai o hashing da arvore eh um pair ordenado, indicando o hashing de cada enraizamento no centroid