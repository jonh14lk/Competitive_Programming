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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100003
#define mod 1000000007

int v[MAXN];

namespace seg
{
  struct node
  {
    int item, lazy, lazy_status, l, r;
  };

  int cnt;
  node seg[500 * MAXN];
  vector<int> roots;

  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a + b;
  }
  int newleaf(int vv)
  {
    int p = ++cnt;
    seg[p].l = 0;
    seg[p].r = 0;
    seg[p].lazy = 0;
    seg[p].lazy_status = 0;
    seg[p].item = vv;
    return p;
  }
  int newparent(int l, int r)
  {
    int p = ++cnt;
    seg[p].l = l;
    seg[p].r = r;
    seg[p].lazy = 0;
    seg[p].lazy_status = 0;
    seg[p].item = merge(seg[seg[p].l].item, seg[seg[p].r].item);
    return p;
  }
  int newkid(int i, int diff, int l, int r)
  {
    int p = ++cnt;
    seg[p].l = seg[i].l;
    seg[p].r = seg[i].r;
    seg[p].lazy = seg[i].lazy + diff;
    seg[p].lazy_status = 1;
    seg[p].item = seg[i].item + ((r - l + 1) * diff);
    return p;
  }
  void add(int i, int l, int r)
  {
    if (!seg[i].lazy_status)
      return;
    if (l != r)
    {
      int mid = (l + r) >> 1;
      seg[i].l = newkid(seg[i].l, seg[i].lazy, l, mid);
      seg[i].r = newkid(seg[i].r, seg[i].lazy, mid + 1, r);
    }
    seg[i].lazy = 0;
    seg[i].lazy_status = 0;
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
      return newleaf(v[l]);
    int mid = (l + r) >> 1;
    return newparent(build(l, mid), build(mid + 1, r));
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int root = seg::build(0, n - 1);
  seg::roots.pb(root);
  while (q--)
  {
    char t;
    cin >> t;
    if (t == 'C')
    {
      int l, r, d;
      cin >> l >> r >> d;
      l--, r--;
      int root = seg::update(seg::roots.back(), 0, n - 1, l, r, d);
      seg::roots.pb(root);
    }
    else if (t == 'Q')
    {
      int l, r;
      cin >> l >> r;
      l--, r--;
      cout << seg::query(0, n - 1, l, r, seg::roots.back()) << endl;
    }
    else if (t == 'H')
    {
      int l, r, d;
      cin >> l >> r >> d;
      l--, r--;
      cout << seg::query(0, n - 1, l, r, seg::roots[d]) << endl;
    }
    else
    {
      int d;
      cin >> d;
      while (seg::roots.size() > d + 1)
        seg::roots.pop_back();
    }
  }
  return 0;
}
// https://www.spoj.com/problems/TTM/
// rollback segtree to a time stamp t
