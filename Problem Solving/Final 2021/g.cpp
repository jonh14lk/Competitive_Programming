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

int curr_hash = 1;
map<vector<int>, int> mp;
unordered_map<int, int> cnt;
unordered_map<int, bool> has;

struct hash_tree
{
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
  int get_hash()
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
    int x = dfs2(c[0], -1);
    int y = dfs2(c[1], -1);
    if (x > y)
      swap(x, y);
    return (x << 30) + y;
  }
};
struct t_tree
{
  int n;
  vector<pi> edges;
  vector<bool> is_root;
  vector<int> roots, label;
  vector<vector<int>> adj;

  void read()
  {
    cin >> n;
    has[n] = 1;
    adj.resize(n);
    label.resize(n);
    is_root.assign(n, 0);
    for (int i = 0; i < n - 1; i++)
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      edges.pb({a, b});
      adj[a].pb(b);
      adj[b].pb(a);
    }
  }
  int dfs(int s, int p, int tam)
  {
    int curr = 1;
    for (auto const &v : adj[s])
    {
      if (v != p)
        curr += dfs(v, s, tam);
    }
    if (curr == tam)
    {
      roots.pb(s);
      is_root[s] = 1;
      return 0;
    }
    return curr;
  }
  void dfs2(int s, int p, int l)
  {
    if (is_root[s])
      l = s;
    label[s] = l;
    for (auto const &v : adj[s])
    {
      if (v != p)
        dfs2(v, s, l);
    }
  }
  int solve(int tam)
  {
    if (!has[tam] || tam == n)
      return 0;
    for (auto const &i : roots)
      is_root[i] = 0;
    roots.clear();
    dfs(0, -1, tam);
    int tot = n / tam;
    if (roots.size() != tot)
      return 0;
    dfs2(0, -1, 0);
    vector<vector<vector<int>>> sub(tot);
    vector<int> kappa(n, 0);
    vector<int> curr_id(n, 0);
    vector<int> id(n, -1);
    vector<int> id2(n, -1);
    for (int i = 0; i < n; i++)
    {
      kappa[label[i]]++;
    }
    for (int i = 0; i < tot; i++)
    {
      id2[roots[i]] = i;
      sub[i].resize(kappa[roots[i]]);
    }
    for (auto const &i : edges)
    {
      if (label[i.fir] == label[i.sec])
      {
        int l = label[i.fir];
        if (id[i.fir] == -1)
          id[i.fir] = curr_id[l]++;
        if (id[i.sec] == -1)
          id[i.sec] = curr_id[l]++;
        sub[id2[l]][id[i.fir]].pb(id[i.sec]);
        sub[id2[l]][id[i.sec]].pb(id[i.fir]);
      }
    }
    int h0 = hash_tree(sub[0]).get_hash();
    for (int i = 1; i < tot; i++)
    {
      int hi = hash_tree(sub[i]).get_hash();
      if (hi != h0)
        return 0;
    }
    return cnt[h0];
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<t_tree> v(n);
  vector<int> h(n);
  for (int i = 0; i < n; i++)
  {
    v[i].read();
    h[i] = hash_tree(v[i].adj).get_hash();
    cnt[h[i]]++;
  }
  for (int i = 0; i < n; i++)
  {
    int ans = cnt[h[i]] - 1, sz = v[i].n;
    for (int j = 1; j <= sqrt(sz); j++)
    {
      if (sz % j == 0)
      {
        ans += v[i].solve(j);
        if (sz / j != j)
          ans += v[i].solve(sz / j);
      }
    }
    cout << ans << " ";
  }
  cout << endl;
  return 0;
}
// hash de arvores
// para descobrir se duas arvores sao isomorfas

// 1 - achar todos os centroides da arvore (toda arvore tem no maximo 2 centroides)
// 2 - achar o hashing com a arvore enraizada em cada centroid
// 3 - dai o hashing da arvore eh um pair ordenado, indicando o hashing de cada enraizamento no centroid

// com isso, voltando pro problema:
// dada uma arvore existe no maximo uma maneira de splitar ela em k arvores do mesmo tamanho
// e eu tenho que verificar para k sendo um divisor de n
// com isso, da pra resolver o problema