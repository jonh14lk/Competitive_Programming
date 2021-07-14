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

namespace seg
{
  int lazy[4 * MAXN];
  int seg[4 * MAXN];

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
    seg[i] += (r - l + 1) * diff;
    if (l != r)
    {
      lazy[i << 1] += diff;
      lazy[(i << 1) | 1] += diff;
    }
    lazy[i] = 0;
  }
  void update(int i, int l, int r, int ql, int qr, int diff)
  {
    if (lazy[i])
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
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
}
namespace rmq
{
  int st[MAXN][25];
  int log[MAXN];

  void build(vector<int> &v)
  {
    int n = v.size();
    log[1] = 0;
    for (int i = 2; i < MAXN; i++)
      log[i] = log[i / 2] + 1;
    for (int i = 0; i < n; i++)
      st[i][0] = v[i];
    for (int j = 1; j <= 25; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  int query(int l, int r)
  {
    int j = log[r - l + 1];
    int minimum = max(st[l][j], st[r - (1 << j) + 1][j]);
    return minimum;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  vector<int> ans(n, 0);
  rmq::build(v);
  for (int i = 0; i < n; i++)
  {
    int l = i, r = n - 1;
    while (l < r)
    {
      int mid = (l + r + 1) >> 1;
      (rmq::query(i, mid) == v[i]) ? l = mid : r = mid - 1;
    }
    int hi;
    if (l + 1 < n)
    {
      l++;
      int sz = (l - i + 1) >> 1;
      hi = i + sz - 1;
    }
    else
    {
      hi = l;
    }
    l = 0, r = i;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      (rmq::query(mid, i) == v[i]) ? r = mid : l = mid + 1;
    }
    int lo;
    if (l - 1 >= 0)
    {
      l--;
      int sz = (i - l + 1) >> 1;
      lo = i - sz + 1;
    }
    else
    {
      lo = l;
    }
    seg::update(1, 0, n - 1, lo, hi, 1);
  }
  for (int i = 0; i < n; i++)
    cout << seg::query(0, n - 1, i, i, 1) - 1 << " ";
  cout << endl;
  return 0;
}