#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

const int inf = 1e18;

struct segtree
{
  int n;
  vector<int> v;
  vector<int> seg;
  vector<int> lazy;

  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, -inf);
    lazy.assign(4 * n, 0);
  }
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return -inf;
  }
  int merge(int a, int b)
  {
    return max(a, b);
  }
  void add(int i, int l, int r, int diff)
  {
    seg[i] += diff;
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
  int qry(int l, int r)
  {
    return query(0, n - 1, l, r, 1);
  }
  void upd(int l, int r, int x)
  {
    update(1, 0, n - 1, l, r, x);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, s;
  cin >> n >> s;
  vector<pii> ev;
  vector<int> ll;
  vector<int> rr;
  vector<int> cc;
  for (int i = 0; i < n; i++)
  {
    int l, r, c;
    cin >> l >> r >> c;
    cc.pb(c);
    ll.pb(l);
    rr.pb(r);
    ev.pb({l, {1, i}});
    ev.pb({r + 1, {0, i}});
  }
  sort(ev.begin(), ev.end());
  vector<int> dp(n, 0);
  int ans = 0;
  segtree on(n);
  int last = 0;
  for (auto const &i : ev)
  {
    int pos = i.fir, type = i.sec.fir, id = i.sec.sec;
    if (pos > last)
    {
      on.upd(0, n - 1, (pos - last) * s);
      last = pos;
    }
    if (type == 1)
    {
      dp[id] = max(ans, on.qry(0, n - 1));
      dp[id] -= cc[id];
      {
        int prv_val = on.qry(id, id);
        on.upd(id, id, -prv_val);
        on.upd(id, id, dp[id]);
      }
    }
    else
    {
      {
        int prv_val = on.qry(id, id);
        on.upd(id, id, -prv_val);
        on.upd(id, id, -inf);
      }
      ans = max(ans, dp[id] + (rr[id] - ll[id] + 1) * s);
    }
  }
  cout << ans << endl;
  return 0;
}