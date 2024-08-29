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
#define MAXN 300005
#define mod 998244353

const int inf = 1e18;

struct segtree
{
  int n;
  vector<int> v;
  vector<int> seg;

  segtree(vector<int> &vv)
  {
    v = vv;
    n = v.size();
    seg.assign(4 * n, 0);
    build(0, n - 1, 1);
  }
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return 1e18;
  }
  int merge(int a, int b)
  {
    return max(a, b);
  }
  void update(int i, int l, int r, int q, int x)
  {
    if (l == r)
    {
      seg[i] = single(x);
      return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
      update(i << 1, l, mid, q, x);
    else
      update((i << 1) | 1, mid + 1, r, q, x);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i, int x)
  {
    if (l == r)
      return (seg[i] >= x && l >= ql) ? l : -1;
    int mid = (l + r) >> 1, at = -1;
    if (seg[i << 1] >= x && mid >= ql)
      at = query(l, mid, ql, qr, i << 1, x);
    if (at == -1)
      at = query(mid + 1, r, ql, qr, (i << 1) | 1, x);
    return at;
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      seg[i] = single(v[l]);
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int x, int l)
  {
    return query(0, n - 1, l, n - 1, 1, x);
  }
  void upd(int x, int l)
  {
    update(1, 0, n - 1, x, l);
  }
};
signed main()
{
  int n, q;
  cin >> n >> q;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  segtree st(v);
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 2)
    {
      int x, l;
      cin >> x >> l; // find the minimum index j such that j >= l and v[j] >= x
      cout << st.qry(x, l) << endl;
    }
    else
    {
      int a, b;
      cin >> a >> b; // v[a] = b;
      st.upd(a, b);
    }
  }
}