//https://www.spoj.com/problems/QTREE/
//Don't use cin/cout in this problem (gives TLE)
#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 10001
#define mod 1000000007
 
int n;
vector<pi> adj[MAXN];
vector<pi> edges;
 
namespace seg
{
  int seg[4 * MAXN];
  int lazy[4 * MAXN];
  int v[MAXN];
 
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return -1;
  }
  int merge(int a, int b)
  {
    return max(a, b);
  }
  void add(int i, int l, int r, int diff)
  {
    seg[i] = (r - l + 1) * diff;
    if (l != r)
    {
      lazy[i << 1] = diff;
      lazy[(i << 1) | 1] = diff;
    }
    lazy[i] = -1;
  }
  void update(int i, int l, int r, int ql, int qr, int diff)
  {
    if (lazy[i] != -1)
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(i, l, r, diff);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, diff);
    update((i << 1) | 1, mid + 1, r, ql, qr, diff);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (lazy[i] != -1)
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      seg[i] = single(v[l]);
      lazy[i] = -1;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
    lazy[i] = -1;
  }
} // namespace seg
namespace hld
{
  int cur_pos;
  vector<int> parent, depth, heavy, head, pos, sz, up;
 
  int dfs(int s)
  {
    int size = 1, max_c_size = 0;
    for (auto const &c : adj[s])
    {
      if (c.fir != parent[s])
      {
        parent[c.fir] = s;
        depth[c.fir] = depth[s] + 1;
        int c_size = dfs(c.fir);
        size += c_size;
        if (c_size > max_c_size)
          max_c_size = c_size, heavy[s] = c.fir;
      }
    }
    return sz[s] = size;
  }
  void decompose(int s, int h)
  {
    head[s] = h;
    pos[s] = cur_pos++;
    seg::v[pos[s]] = up[s];
    for (auto const &c : adj[s])
    {
      if (c.fir != parent[s] && c.fir == heavy[s])
      {
        up[c.fir] = c.sec;
        decompose(heavy[s], h);
      }
    }
    for (auto const &c : adj[s])
    {
      if (c.fir != parent[s] && c.fir != heavy[s])
      {
        up[c.fir] = c.sec;
        decompose(c.fir, c.fir);
      }
    }
  }
  void init()
  {
    parent.assign(MAXN, -1);
    depth.assign(MAXN, -1);
    heavy.assign(MAXN, -1);
    head.assign(MAXN, -1);
    pos.assign(MAXN, -1);
    sz.assign(MAXN, 1);
    up.assign(MAXN, 0);
    cur_pos = 0;
    dfs(0);
    decompose(0, 0);
    seg::build(0, n - 1, 1);
  }
  int query_path(int a, int b)
  {
    int res = -1;
    for (; head[a] != head[b]; b = parent[head[b]])
    {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);
      res = max(res, seg::query(0, n - 1, pos[head[b]], pos[b], 1));
    }
    if (depth[a] > depth[b])
      swap(a, b);
    res = max(res, seg::query(0, n - 1, pos[a] + 1, pos[b], 1));
    return res;
  }
  void update_path(int a, int b, int x)
  {
    for (; head[a] != head[b]; b = parent[head[b]])
    {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);
      seg::update(1, 0, n - 1, pos[head[b]], pos[b], x);
    }
    if (depth[a] > depth[b])
      swap(a, b);
    seg::update(1, 0, n - 1, pos[a] + 1, pos[b], x);
  }
  void update_subtree(int a, int x)
  {
    seg::update(1, 0, n - 1, pos[a] + 1, pos[a] + sz[a] - 1, x);
  }
  int query_subtree(int a, int x)
  {
    return seg::query(0, n - 1, pos[a] + 1, pos[a] + sz[a] - 1, 1);
  }
} // namespace hld
signed main()
{
  int q;
  scanf("%d", &q);
  while (q--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      adj[i].clear();
    edges.clear();
    for (int i = 0; i < n - 1; i++)
    {
      int a, b, c;
      scanf("%d %d %d", &a, &b, &c);
      a--, b--;
      adj[a].pb({b, c});
      adj[b].pb({a, c});
      edges.pb({a, b});
    }
    hld::init();
    while (true)
    {
      char k[10];
      scanf("%s", k);
      if (k[0] == 'Q')
      {
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        printf("%d\n", hld::query_path(a, b));
      }
      else if (k[0] == 'C')
      {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        hld::update_path(edges[a].fir, edges[a].sec, b);
      }
      else
      {
        break;
      }
    }
  }
  return 0;
} 
