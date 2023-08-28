
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

struct item
{
  int sg_max, pref_max, suf_max, sg_min, pref_min, suf_min, sum;
};
struct segtree
{
  int n;
  vector<item> seg;

  item single(int x)
  {
    return {max(0ll, x), max(0ll, x), max(0ll, x), min(0ll, x), min(0ll, x), min(0ll, x), x};
  }
  item neutral()
  {
    return {0, 0, 0, 0, 0, 0, 0};
  }
  segtree() {}
  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, neutral());
  }
  item merge(item a, item b)
  {
    item ret;
    ret.sg_max = max({a.sg_max, b.sg_max, a.suf_max + b.pref_max});
    ret.pref_max = max(a.pref_max, a.sum + b.pref_max);
    ret.suf_max = max(b.suf_max, b.sum + a.suf_max);
    ret.sg_min = min({a.sg_min, b.sg_min, a.suf_min + b.pref_min});
    ret.pref_min = min(a.pref_min, a.sum + b.pref_min);
    ret.suf_min = min(b.suf_min, b.sum + a.suf_min);
    ret.sum = a.sum + b.sum;
    return ret;
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
  item query(int l, int r, int ql, int qr, int i)
  {
    int mid = (l + r) >> 1;
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i];
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
};
signed main()
{
  return 0;
}
// segtree for maximum segment sum
// me enrolo pra codar toda vez, e bom deixar na lib