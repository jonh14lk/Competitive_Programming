#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

namespace seg
{
  struct node
  {
    int item, lazy, l, r;
    node() {}
    node(int l, int r, int lazy, int item) : l(l), r(r), lazy(lazy), item(item) {}
  };
  struct wtf
  {
    int sz, i, l, r, lazy;
  };

  vector<node> seg;
  vector<wtf> ops;

  void init()
  {
    seg.resize(1);
    ops.clear();
  }
  int neutral()
  {
    return 2e9;
  }
  int merge(int a, int b)
  {
    return min(a, b);
  }
  int newleaf(int vv)
  {
    int p = seg.size();
    seg.pb(node(0, 0, 0, vv));
    return p;
  }
  int newparent(int l, int r)
  {
    int p = seg.size();
    seg.pb(node(l, r, 0, merge(seg[l].item, seg[r].item)));
    return p;
  }
  int newkid(int i, int diff, int l, int r)
  {
    int p = seg.size();
    seg.pb(node(seg[i].l, seg[i].r, max(seg[i].lazy, diff), max(seg[i].item, diff)));
    return p;
  }
  void add(int i, int l, int r)
  {
    if (!seg[i].lazy)
      return;
    if (l != r)
    {
      int mid = (l + r) >> 1;
      int prvl = seg[i].l, prvr = seg[i].r;
      seg[i].l = newkid(seg[i].l, seg[i].lazy, l, mid);
      seg[i].r = newkid(seg[i].r, seg[i].lazy, mid + 1, r);
      ops.pb({(int)seg.size(), i, prvl, prvr, seg[i].lazy});
    }
    seg[i].lazy = 0;
  }
  int update(int i, int l, int r, int ql, int qr, int diff)
  {
    if (l > r || l > qr || r < ql)
      return i;
    if (l >= ql && r <= qr)
      return newkid(i, diff, l, r);
    add(i, l, r);
    int mid = (l + r) >> 1;
    return newparent(update(seg[i].l, l, mid, ql, qr, diff), update(seg[i].r, mid + 1, r, ql, qr, diff));
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i].item;
    add(i, l, r);
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, seg[i].l), query(mid + 1, r, ql, qr, seg[i].r));
  }
  int build(int l, int r)
  {
    if (l == r)
      return newleaf(0);
    int mid = (l + r) >> 1;
    return newparent(build(l, mid), build(mid + 1, r));
  }
  void rollback_to(int x)
  {
    int new_sz = x + 1;
    while (ops.size() > 0 && ops.back().sz > new_sz)
    {
      seg[ops.back().i].l = ops.back().l;
      seg[ops.back().i].r = ops.back().r;
      seg[ops.back().i].lazy = ops.back().lazy;
      ops.pop_back();
    }
    while (seg.size() > new_sz)
    {
      seg.pop_back();
    }
  }
}

struct query
{
  int t, a, b, h;
};

int seg_root;
vector<int> seg_stack;
vector<int> vals;
query v[MAXN];
int tin[MAXN];
int tout[MAXN];
int pos[MAXN];
int ans[MAXN];
vector<int> t[4 * MAXN];

void add(int i, int l, int r, int ql, int qr, int q_id)
{
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    t[i].pb(q_id);
    return;
  }
  int mid = (l + r) >> 1;
  add((i << 1), l, mid, ql, qr, q_id);
  add((i << 1) | 1, mid + 1, r, ql, qr, q_id);
}
void dfs(int i, int l, int r)
{
  for (auto const &q_id : t[i])
  {
    seg_root = seg::update(seg_root, 0, vals.size() - 1, v[q_id].a, v[q_id].b, v[q_id].h);
  }
  seg_stack.pb(seg_root);
  if (l == r)
  {
    if (v[l].t == 2)
      ans[l] = seg::query(0, vals.size() - 1, v[l].a, v[l].b, seg_root);
  }
  else
  {
    int mid = (l + r) >> 1;
    dfs((i << 1), l, mid);
    dfs((i << 1) | 1, mid + 1, r);
  }
  seg_stack.pop_back();
  seg_root = seg_stack.back();
  seg::rollback_to(seg_root);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int curr_id = 1;
  for (int i = 0; i < n; i++)
  {
    char c;
    cin >> c;
    if (c == '+')
    {
      int a, b, h;
      cin >> a >> b >> h;
      b--;
      v[i] = {0, a, b, h};
      vals.pb(a);
      vals.pb(b);
      vals.pb(b + 1);
      pos[curr_id] = i;
      tin[curr_id] = i;
      tout[curr_id] = n;
      curr_id++;
    }
    else if (c == '-')
    {
      int a;
      cin >> a;
      v[i] = {1, a, -1, -1};
      tout[a] = i;
    }
    else
    {
      int a, b;
      cin >> a >> b;
      b--;
      v[i] = {2, a, b, -1};
      vals.pb(a);
      vals.pb(b);
      vals.pb(b + 1);
    }
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  for (int i = 0; i < n; i++)
  {
    if (v[i].t != 1)
    {
      v[i].a = lower_bound(vals.begin(), vals.end(), v[i].a) - vals.begin();
      v[i].b = lower_bound(vals.begin(), vals.end(), v[i].b) - vals.begin();
    }
  }
  for (int i = 1; i < curr_id; i++)
  {
    add(1, 0, n, tin[i], tout[i], pos[i]);
  }
  seg_root = seg::build(0, vals.size() - 1);
  seg_stack.pb(seg_root);
  dfs(1, 0, n);
  for (int i = 0; i < n; i++)
  {
    if (v[i].t == 2)
      cout << ans[i] << endl;
  }
  return 0;
}