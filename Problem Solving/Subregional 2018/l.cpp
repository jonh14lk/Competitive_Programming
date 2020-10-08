#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<string, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 20
#define mod 998244353

int n, q, cur_pos;
vector<int> bit, bit2;
vector<int> adj[MAXN];
vector<int> parent, depth, heavy, head, pos;

void add1(int idx, int delta)
{
  for (; idx < n; idx = idx | (idx + 1))
    bit[idx] += delta;
}
void add2(int idx, int delta)
{
  for (; idx < n; idx = idx | (idx + 1))
    bit2[idx] += delta;
}
void update_range(int val, int l, int r)
{
  add1(l, val);
  add1(r + 1, -val);
  add2(l, val * (l - 1));
  add2(r + 1, -val * r);
}
int sum1(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += bit[r];
  return ret;
}
int sum2(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += bit2[r];
  return ret;
}
int sum(int x)
{
  return (sum1(x) * x) - sum2(x);
}
int range_sum(int l, int r)
{
  return sum(r) - sum(l - 1);
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
  bit.assign(MAXN, 0);
  bit2.assign(MAXN, 0);
  cur_pos = 0;
  dfs(0);
  decompose(0, 0);
}
int query(int a, int b)
{
  int res = 0;
  for (; head[a] != head[b]; b = parent[head[b]])
  {
    if (depth[head[a]] > depth[head[b]])
      swap(a, b);
    int cur_heavy_path_max = range_sum(pos[head[b]], pos[b]);
    res += cur_heavy_path_max;
  }
  if (depth[a] > depth[b])
    swap(a, b);
  int last_heavy_path_max = range_sum(pos[a], pos[b]);
  res += last_heavy_path_max;
  return res;
}
void update_path(int a, int b, int x)
{
  for (; head[a] != head[b]; b = parent[head[b]])
  {
    if (depth[head[a]] > depth[head[b]])
      swap(a, b);
    update_range(x, pos[head[b]], pos[b]);
  }
  if (depth[a] > depth[b])
    swap(a, b);
  update_range(x, pos[a], pos[b]);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  init();
  while (q--)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    update_path(a, b, 1);
    cout << query(c, d) << endl;
    update_path(a, b, -1);
  }
  return 0;
}