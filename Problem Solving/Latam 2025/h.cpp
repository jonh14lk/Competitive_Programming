#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005

template <int p>
struct mod_int
{
  int expo(int b, int e)
  {
    int ret = 1;
    while (e)
    {
      if (e % 2)
        ret = ret * b % p;
      e /= 2, b = b * b % p;
    }
    return ret;
  }
  int inv(int b) { return expo(b, p - 2); }

  using m = mod_int;
  int v;
  mod_int() : v(0) {}
  mod_int(int v_)
  {
    if (v_ >= p or v_ <= -p)
      v_ %= p;
    if (v_ < 0)
      v_ += p;
    v = v_;
  }
  m &operator+=(const m &a)
  {
    v += a.v;
    if (v >= p)
      v -= p;
    return *this;
  }
  m &operator-=(const m &a)
  {
    v -= a.v;
    if (v < 0)
      v += p;
    return *this;
  }
  m &operator*=(const m &a)
  {
    v = v * 1ll * (a.v) % p;
    return *this;
  }
  m &operator/=(const m &a)
  {
    v = v * inv(a.v) % p;
    return *this;
  }
  m operator-() { return m(-v); }
  m &operator^=(int e)
  {
    if (e < 0)
    {
      v = inv(v);
      e = -e;
    }
    v = expo(v, e);
    return *this;
  }
  bool operator==(const m &a) { return v == a.v; }
  bool operator!=(const m &a) { return v != a.v; }

  friend istream &operator>>(istream &in, m &a)
  {
    int val;
    in >> val;
    a = m(val);
    return in;
  }
  friend ostream &operator<<(ostream &out, m a)
  {
    return out << a.v;
  }
  friend m operator+(m a, m b) { return a += b; }
  friend m operator-(m a, m b) { return a -= b; }
  friend m operator*(m a, m b) { return a *= b; }
  friend m operator/(m a, m b) { return a /= b; }
  friend m operator^(m a, int e) { return a ^= e; }
};

const int MOD = 998244353;
typedef mod_int<MOD> mint;

void ntt(vector<mint> &a, bool rev)
{
  int n = a.size();
  auto b = a;
  assert(!(n & (n - 1)));
  mint g = 1;
  while ((g ^ (MOD / 2)) == 1)
    g += 1;
  if (rev)
    g = 1 / g;

  for (int step = n / 2; step; step /= 2)
  {
    mint w = g ^ (MOD / (n / step)), wn = 1;
    for (int i = 0; i < n / 2; i += step)
    {
      for (int j = 0; j < step; j++)
      {
        auto u = a[2 * i + j], v = wn * a[2 * i + j + step];
        b[i + j] = u + v;
        b[i + n / 2 + j] = u - v;
      }
      wn = wn * w;
    }
    swap(a, b);
  }
  if (rev)
  {
    auto n1 = mint(1) / n;
    for (auto &x : a)
      x *= n1;
  }
}
vector<mint> convolution(const vector<mint> &a, const vector<mint> &b)
{
  vector<mint> l(a.begin(), a.end()), r(b.begin(), b.end());
  int N = l.size() + r.size() - 1, n = 1;
  while (n <= N)
    n *= 2;
  l.resize(n);
  r.resize(n);
  ntt(l, false);
  ntt(r, false);
  for (int i = 0; i < n; i++)
    l[i] *= r[i];
  ntt(l, true);
  l.resize(N);
  return l;
}

int n;
vector<int> adj[MAXN];
mint ans[MAXN];

namespace lca
{
  int l, timer;
  vector<int> tin, tout, depth, sz;
  vector<vector<int>> up;

  void dfs(int v, int p)
  {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; i++)
      up[v][i] = up[up[v][i - 1]][i - 1];
    sz[v] = 1;
    for (auto const &u : adj[v])
    {
      if (p == u)
        continue;
      depth[u] = depth[v] + 1;
      dfs(u, v);
      sz[v] += sz[u];
    }
    tout[v] = ++timer;
  }
  bool is_ancestor(int u, int v)
  {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
  int get(int u, int v) // subtree_size[u] when the tree root is v
  {
    if (u == v)
      return n;
    if (!is_ancestor(u, v))
      return sz[u];
    int diff = (depth[v] - depth[u]) - 1;
    for (int i = l; i >= 0; i--)
      if (diff & (1 << i))
        v = up[v][i];
    return n - sz[v];
  }
  void init()
  {
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    sz.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(0, 0);
  }
}
namespace cd
{
  int sz;
  vector<int> subtree_size;
  vector<bool> visited;
  vector<mint> cntsq;

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
  void dfs2(int s, int f, int d, int r)
  {
    while (d >= cntsq.size())
      cntsq.pb(0);
    int sub_size = lca::get(s, r); // subtree_size[s] when the tree root is r
    cntsq[d] += (sub_size * sub_size);
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
        dfs2(v, s, d + 1, r);
    }
  }
  int dfs_sz(int s, int f)
  {
    int ans = 1;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
        ans += dfs_sz(v, s);
    }
    return ans;
  }
  void solve(int s)
  {
    vector<pi> ord;
    for (auto const &v : adj[s])
    {
      if (!visited[v])
        ord.pb({dfs_sz(v, s), v});
    }
    sort(ord.begin(), ord.end());
    vector<mint> totsq(1, 0);
    for (auto [_, v] : ord)
    {
      cntsq.clear();
      dfs2(v, s, 1, s);
      int sub_size = lca::get(v, s);
      totsq[0] = (n - sub_size) * (n - sub_size); // vertical paths from s to some vertex on v subtree
      vector<mint> a = convolution(totsq, cntsq);
      for (int i = 1; i < a.size(); i++)
      {
        ans[i] += a[i];
      }
      for (int i = 1; i < cntsq.size(); i++)
      {
        while (i >= totsq.size())
          totsq.pb(0);
        totsq[i] += cntsq[i];
      }
    }
  }
  int decompose_tree(int s)
  {
    sz = 0;
    dfs(s, s);
    int cend_tree = get_centroid(s, s);
    visited[cend_tree] = 1;
    solve(cend_tree);
    for (auto const &v : adj[cend_tree])
    {
      if (!visited[v])
        decompose_tree(v);
    }
    return cend_tree;
  }
  void init()
  {
    subtree_size.resize(n);
    visited.resize(n);
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
  lca::init();
  cd::init();
  // i want to improve this
  // for (int i = n - 1; i >= 1; i--)
  // {
  //   for (int j = i - 1; j >= 1; j--)
  //     ans[j] -= (i - j + 1) * ans[i];
  // }
  mint sum = 0;
  mint tot = 0;
  for (int j = n - 1; j >= 1; j--)
  {
    ans[j] -= tot - (j * sum);
    tot += (j + 1) * ans[j];
    sum += ans[j];
  }
  for (int i = 1; i < n; i++)
    cout << ans[i] << " ";
  cout << endl;
  return 0;
}