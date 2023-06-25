// https://codeforces.com/contest/343/problem/D
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 500001
#define mod 1000000007

struct segtree
{
  int n;
  vector<int> v;
  vector<int> seg;
  vector<int> lazy;

  segtree() {}
  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, 0);
    lazy.assign(4 * n, -1);
  }
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a + b;
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
};
struct hld
{
  int n, cur_pos;
  segtree seg;
  vector<vector<int>> adj;
  vector<int> parent, depth, heavy, head, pos, sz;

  int dfs(int s)
  {
    int size = 1, max_c_size = 0;
    for (auto const &c : adj[s])
    {
      if (c != parent[s])
      {
        parent[c] = s;
        depth[c] = depth[s] + 1;
        int c_size = dfs(c);
        size += c_size;
        if (c_size > max_c_size)
          max_c_size = c_size, heavy[s] = c;
      }
    }
    return sz[s] = size;
  }
  void decompose(int s, int h)
  {
    head[s] = h;
    pos[s] = cur_pos++;
    if (heavy[s] != -1)
      decompose(heavy[s], h);
    for (int c : adj[s])
    {
      if (c != parent[s] && c != heavy[s])
        decompose(c, c);
    }
  }
  hld(vector<vector<int>> &g)
  {
    n = g.size();
    adj = g;
    seg = segtree(n);
    parent.assign(n, -1);
    depth.assign(n, -1);
    heavy.assign(n, -1);
    head.assign(n, -1);
    pos.assign(n, -1);
    sz.assign(n, 1);
    cur_pos = 0;
    dfs(0);
    decompose(0, 0);
  }
  int query_path(int a, int b)
  {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]])
    {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);
      res += seg.query(0, n - 1, pos[head[b]], pos[b], 1);
    }
    if (depth[a] > depth[b])
      swap(a, b);
    res += seg.query(0, n - 1, pos[a], pos[b], 1);
    return res;
  }
  void update_path(int a, int b, int x)
  {
    for (; head[a] != head[b]; b = parent[head[b]])
    {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);
      seg.update(1, 0, n - 1, pos[head[b]], pos[b], x);
    }
    if (depth[a] > depth[b])
      swap(a, b);
    seg.update(1, 0, n - 1, pos[a], pos[b], x);
  }
  void update_subtree(int a, int x)
  {
    seg.update(1, 0, n - 1, pos[a], pos[a] + sz[a] - 1, x);
  }
  int query_subtree(int a)
  {
    return seg.query(0, n - 1, pos[a], pos[a] + sz[a] - 1, 1);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  hld h(adj);
  int q;
  cin >> q;
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    b--;
    if (a == 1)
    {
      h.update_subtree(b, 1);
    }
    if (a == 2)
    {
      h.update_path(0, b, 0);
    }
    if (a == 3)
    {
      cout << h.query_path(b, b) << endl;
    }
  }
  return 0;
}
