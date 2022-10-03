#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct lazy_node
{
  int n, a, d;

  int sum()
  {
    int an = a + (d * (n - 1));
    return ((a + an) * n) >> 1;
  }
  void merge(lazy_node to_add)
  {
    a += to_add.a;
    d += to_add.d;
  }
};
struct segtree
{
  vector<int> seg;
  vector<lazy_node> lazy;
  vector<bool> lazy_status;

  segtree(int n)
  {
    seg.resize(4 * n);
    lazy.resize(4 * n);
    lazy_status.resize(4 * n);
    build(0, n - 1, 1);
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
  void add(int i, int l, int r, lazy_node to_add)
  {
    seg[i] += to_add.sum();
    if (l != r)
    {
      int mid = (l + r) >> 1;
      lazy[i << 1].merge({mid - l + 1, to_add.a, to_add.d});
      lazy_status[i << 1] = 1;
      int diff = (mid + 1) - l, a = to_add.a, d = to_add.d;
      lazy[(i << 1) | 1].merge({r - (mid + 1) + 1, a + (d * diff), d});
      lazy_status[(i << 1) | 1] = 1;
    }
    lazy[i] = {r - l + 1, 0, 0};
    lazy_status[i] = 0;
  }
  void update(int i, int l, int r, int ql, int qr, lazy_node to_add)
  {
    if (lazy_status[i])
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      int diff = l - ql, a = to_add.a, d = to_add.d;
      lazy_node curr = {r - l + 1, a + (d * diff), d};
      add(i, l, r, curr);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, to_add);
    update((i << 1) | 1, mid + 1, r, ql, qr, to_add);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (lazy_status[i])
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
    seg[i] = 0;
    lazy_status[i] = 0;
    lazy[i] = {r - l + 1, 0, 0};
    if (l == r)
      return;
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  segtree s(n);
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int l, r, a, d;
      cin >> l >> r >> a >> d;
      l--, r--;
      s.update(1, 0, n - 1, l, r, {r - l + 1, a, d});
    }
    else
    {
      int x;
      cin >> x;
      x--;
      cout << s.query(0, n - 1, x, x, 1) << endl;
    }
  }
  return 0;
}
// queries of:
// add an arithmetic progression to a segment [l, r]
// print current value of a given element