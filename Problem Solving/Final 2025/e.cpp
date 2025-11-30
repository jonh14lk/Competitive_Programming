#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 300005
#define pi pair<int, int>
#define fir first
#define sec second

struct segtree
{
  int n;
  vector<int> seg;
  vector<int> lazy;

  segtree(int sz)
  {
    n = sz;
    seg.resize(4 * n);
    lazy.assign(4 * n, 0);
    build(0, n - 1, 1);
  }
  void add(int i, int l, int r, int x)
  {
    seg[i] += x;
    if (l != r)
    {
      lazy[i << 1] += x;
      lazy[(i << 1) + 1] += x;
    }
    lazy[i] = 0;
  }
  void upd(int i, int l, int r, int ql, int qr, int x)
  {
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r or l > qr or r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(i, l, r, x);
      return;
    }
    int mid = (l + r) >> 1;
    upd(i << 1, l, mid, ql, qr, x);
    upd((i << 1) + 1, mid + 1, r, ql, qr, x);
    seg[i] = min(seg[i << 1], seg[(i << 1) + 1]);
  }
  int qry(int i, int l, int r, int ql, int qr)
  {
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r or l > qr or r < ql)
      return 1e18;
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return min(qry(i << 1, l, mid, ql, qr), qry((i << 1) + 1, mid + 1, r, ql, qr));
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      seg[i] = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) + 1);
    seg[i] = min(seg[i << 1], seg[(i << 1) + 1]);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  int qt = 0;
  segtree st(MAXN);
  while (q--)
  {
    char c;
    int x;
    cin >> c >> x;
    if (c == '+')
    {
      qt++;
      st.upd(1, 0, MAXN - 1, 0, MAXN - 1, 1);
      if (x < MAXN)
      {
        st.upd(1, 0, MAXN - 1, x, MAXN - 1, -1);
      }
    }
    else
    {
      qt--;
      st.upd(1, 0, MAXN - 1, 0, MAXN - 1, -1);
      if (x < MAXN)
      {
        st.upd(1, 0, MAXN - 1, x, MAXN - 1, 1);
      }
    }
    int curr = st.qry(1, 0, MAXN - 1, 0, MAXN - 1);
    cout << curr << " ";
  }
  cout << endl;
}