#include <bits/stdc++.h> // hld com seg de maximo
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<string, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200001
#define MAXL 20
#define mod 998244353

int n, cur_pos;
int seg[4 * MAXN];
vector<int> adj[MAXN];
vector<int> parent, depth, heavy, head, pos;

int seg_query(int i, int l, int r, int ql, int qr)
{
  if (l >= ql && r <= qr)
    return seg[i];
  if (l > qr || r < ql)
    return -1;
  int mid = (l + r) / 2;
  return max(seg_query(2 * i, l, mid, ql, qr), seg_query((2 * i) + 1, mid + 1, r, ql, qr));
}
void seg_update(int i, int l, int r, int pos, int x)
{
  if (l == r)
    seg[i] = x;
  else
  {
    int mid = (l + r) / 2;
    if (pos <= mid)
      seg_update(2 * i, l, mid, pos, x);
    else
      seg_update((2 * i) + 1, mid + 1, r, pos, x);
    seg[i] = max(seg[2 * i], seg[(2 * i) + 1]);
  }
}
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
  return size;
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
void init()
{
  parent.assign(MAXN, -1);
  depth.assign(MAXN, -1);
  heavy.assign(MAXN, -1);
  head.assign(MAXN, -1);
  pos.assign(MAXN, -1);
  cur_pos = 0;
  dfs(0);
  decompose(0, 0);
  for (int i = 0; i < n; i++)
    seg_update(1, 0, n - 1, pos[i], i);
}
int query(int a, int b)
{
  int res = 0;
  for (; head[a] != head[b]; b = parent[head[b]])
  {
    if (depth[head[a]] > depth[head[b]])
      swap(a, b);
    int cur_heavy_path_max = seg_query(1, 0, n - 1, pos[head[b]], pos[b]);
    res = max(res, cur_heavy_path_max);
  }
  if (depth[a] > depth[b])
    swap(a, b);
  int last_heavy_path_max = seg_query(1, 0, n - 1, pos[a], pos[b]);
  res = max(res, last_heavy_path_max);
  return res;
}
signed main()
{
  cin >> n;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  init();
  int q;
  cin >> q;
  while (q--)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    cout << query(a, b) + 1 << endl;
  }
  return 0;
}
