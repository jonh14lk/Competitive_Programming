#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10004

using namespace std;

template <typename T>
bool ckmin(T &a, T b) { return a > b ? a = b, true : false; }

const ll INF = 1e18;

struct Leftist
{
  Leftist *l, *r;
  ll key;
  vector<pair<ll, int>>::iterator info;

  Leftist(ll key, vector<pair<ll, int>>::iterator info) : l(nullptr), r(nullptr), key(key), info(info) {}

  static void insert(Leftist *&root, ll key, vector<pair<ll, int>>::iterator info)
  {
    if (!root || key < root->key)
    {
      Leftist *x = new Leftist(key, info);
      swap(x, root);
      root->l = x;
      return;
    }
    root = new Leftist(*root);
    swap(root->l, root->r);
    insert(root->r, key, info);
  }
};

struct Edge
{
  int u, v;
  ll w;

  Edge(int u = -1, int v = -1, ll w = -1) : u(u), v(v), w(w) {}
};

vector<ll> kth_shortest_paths(int n, int src, int dest, int k, vector<Edge> &edges)
{
  int m = (int)edges.size();
  vector<ll> dist(n, INF);
  vector<int> topo_sort, prv(n, -1), vis(n);
  vector<vector<pair<int, int>>> rgraph(n);
  topo_sort.reserve(n);

  for (int i = 0; i < m; ++i)
  {
    auto &[u, v, w] = edges[i];
    w *= -1;
    rgraph[v].push_back(make_pair(u, i));
  }

  function<void(int)> dfs = [&](int u)
  {
    vis[u] = 1;
    for (auto [v, i] : rgraph[u])
    {
      if (!vis[v])
        dfs(v);
    }
    topo_sort.push_back(u);
  };

  auto topo = [&]()
  {
    dfs(dest);
    reverse(topo_sort.begin(), topo_sort.end());
    dist[dest] = 0;
    for (int u : topo_sort)
    {
      for (auto [v, i] : rgraph[u])
      {
        if (ckmin(dist[v], dist[u] + edges[i].w))
        {
          prv[v] = i;
        }
      }
    }
  };
  topo();
  if (dist[src] == INF)
    return {};

  vector<vector<pair<ll, int>>> adj(n + 1);

  for (int i = 0; i < m; ++i)
  {
    auto &[u, v, w] = edges[i];
    if (dist[v] == INF || i == prv[u])
      continue;
    w += dist[v] - dist[u];
    adj[u].push_back(make_pair(w, v));
  }

  adj[n] = {make_pair(0, src), make_pair(INF, -1)};

  vector<Leftist *> hp(n);
  for (int u : topo_sort)
  {
    sort(adj[u].begin(), adj[u].end());
    if (u != dest && prv[u] != -1)
    {
      int v = edges[prv[u]].v;
      hp[u] = hp[v];
    }
    if (!adj[u].empty())
    {
      adj[u].push_back(make_pair(INF, -1));
      auto &[w, v] = adj[u][0];
      Leftist::insert(hp[u], w, adj[u].begin());
    }
  }

  vector<ll> res;
  res.reserve(k);

  using tllp = tuple<ll, Leftist *, vector<pair<ll, int>>::iterator>;

  auto cmp = [](const tllp &a, const tllp &b)
  {
    return get<0>(a) > get<0>(b);
  };

  priority_queue<tllp, vector<tllp>, decltype(cmp)> pq(cmp);
  pq.push({dist[src], nullptr, adj[n].begin()});
  while (!pq.empty() && (int)res.size() < k)
  {
    auto [w, x, it] = pq.top();
    pq.pop();
    res.push_back(w);
    auto &[nw, v] = *it;
    if ((++it)->second != -1)
      pq.push({w + it->first - nw, nullptr, it});
    if (hp[v])
      pq.push({w + hp[v]->key, hp[v], hp[v]->info});
    if (x)
    {
      if (x->l)
        pq.push({w + x->l->key - nw, x->l, x->l->info});
      if (x->r)
        pq.push({w + x->r->key - nw, x->r, x->r->info});
    }
  }
  return res;
}

int n, k;
int a[MAXN];
int b[MAXN];
int pos[MAXN];
vector<pi> seg[4 * MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    a[i]--;
    pos[a[i]] = i;
  }
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }
  int m = n + 2, s = n, t = n + 1;
  vector<Edge> edges;
  for (int i = 0; i < n; i++) // arestas iniciais
  {
    edges.pb({s, i, b[i]});
    edges.pb({i, t, 0});
  }
  auto build = [&](auto &&self, int l, int r, int i) -> void
  {
    for (int j = l; j <= r; j++)
    {
      edges.pb({m, pos[j], b[pos[j]]});
      seg[i].pb({pos[j], m});
      m++;
    }
    sort(seg[i].begin(), seg[i].end());
    for (int j = 1; j < seg[i].size(); j++)
    {
      edges.pb({seg[i][j - 1].sec, seg[i][j].sec, 0});
    }
    if (l != r)
    {
      int mid = (l + r) >> 1;
      self(self, l, mid, i << 1);
      self(self, mid + 1, r, (i << 1) | 1);
    }
  };
  auto add_edges = [&](auto &&self, int l, int r, int ql, int qr, int i, int idx) -> void
  {
    if (l > r || l > qr || r < ql || ql > qr)
    {
      return;
    }
    if (l >= ql && r <= qr)
    {
      auto it = upper_bound(seg[i].begin(), seg[i].end(), pi(idx, -1));
      if (it != seg[i].end())
      {
        int dale = it - seg[i].begin();
        edges.pb({idx, seg[i][dale].sec, 0});
      }
      return;
    }
    int mid = (l + r) >> 1;
    self(self, l, mid, ql, qr, i << 1, idx);
    self(self, mid + 1, r, ql, qr, (i << 1) | 1, idx);
  };
  build(build, 0, n - 1, 1);
  for (int i = 0; i < n; i++)
    add_edges(add_edges, 0, n - 1, a[i] + 1, n - 1, 1, i);
  vector<ll> res = kth_shortest_paths(m, s, t, k, edges);
  for (int i = 0; i < (int)res.size(); i++)
    cout << -res[i] << " ";
  for (int i = res.size() + 1; i <= k; i++)
    cout << -1 << " ";
  cout << endl;
  return 0;
}
// ideia de tfg, mt braba
// passa em 265ms no cf
// eh diferente do editorial, mas eh uma boa modelagem