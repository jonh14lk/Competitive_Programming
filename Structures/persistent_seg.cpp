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
#define mod 1000000007

int n;
vector<int> v;

namespace seg_pers
{
  struct item
  {
    int sum, l, r;
  };

  int time;
  vector<item> seg;
  vector<int> parents;

  void update(int i, int l, int r, int q, int x)
  {
    seg.pb({0, 0, 0});
    int curr = ++time;
    if (l == r)
    {
      seg[curr].sum = x;
      return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
    {
      seg[curr].l = time + 1;
      seg[curr].r = seg[i].r;
      update(seg[i].l, l, mid, q, x);
    }
    else
    {
      seg[curr].l = seg[i].l;
      seg[curr].r = time + 1;
      update(seg[i].r, mid + 1, r, q, x);
    }
    seg[curr].sum = seg[seg[curr].l].sum + seg[seg[curr].r].sum;
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    int mid = (l + r) >> 1;
    if (l > r || l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return seg[i].sum;
    return query(l, mid, ql, qr, seg[i].l) + query(mid + 1, r, ql, qr, seg[i].r);
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      seg[i].sum = v[l];
      return;
    }
    int mid = (l + r) >> 1;
    seg.pb({0, 0, 0});
    seg[i].l = ++time;
    build(l, mid, seg[i].l);
    seg.pb({0, 0, 0});
    seg[i].r = ++time;
    build(mid + 1, r, seg[i].r);
    seg[i].sum = seg[seg[i].l].sum + seg[seg[i].r].sum;
  }
  void init()
  {
    time = 1;
    seg.resize(2);
    parents.resize(1);
    parents[0] = 1;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  seg_pers::init();
  seg_pers::build(0, n - 1, 1);
  int q;
  cin >> q;
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1) // update
    {
      int i, x;
      cin >> i >> x;
      i--;
      seg_pers::parents.pb(seg_pers::time + 1);
      seg_pers::update(seg_pers::parents[seg_pers::parents.size() - 2], 0, n - 1, i, x);
    }
    else if (t == 2) // query
    {
      int l, r;
      cin >> l >> r;
      l--, r--;
      seg_pers::parents.pb(seg_pers::parents.back());
      cout << seg_pers::query(0, n - 1, l, r, seg_pers::parents.back()) << endl;
    }
    else // rollback
    {
      int k;
      cin >> k;
      seg_pers::parents.pb(seg_pers::parents[k]);
    }
  }
  return 0;
}
