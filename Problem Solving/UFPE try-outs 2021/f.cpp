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
#define MAXN 200001
#define mod 1000000007

const int d = 227;
int pot[MAXN];

///// modular operations template
int modpow(int x, int y)
{
  int z = 1;
  while (y)
  {
    if (y & 1)
      z = (z * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return z;
}
int inverse(int x)
{
  return modpow(x, mod - 2);
}
int divide(int x, int y)
{
  return (x * inverse(y)) % mod;
}
int subtract(int x, int y)
{
  return ((x + mod) - y) % mod;
}
int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int sum(int x, int y)
{
  return (x + y) % mod;
}
////////////////////////////////
struct seg
{
  string s;
  vector<int> seg;

  int merge(int a, int al, int b, int bl)
  {
    a = sum(multiplicate(a, pot[bl]), b);
    return a;
  }
  void update(int i, int l, int r, int q, int x)
  {
    if (l == r)
    {
      seg[i] = x;
      return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
      update(i << 1, l, mid, q, x);
    else
      update((i << 1) | 1, mid + 1, r, q, x);
    seg[i] = merge(seg[i << 1], mid - l + 1, seg[(i << 1) | 1], r - (mid + 1) + 1);
  }
  pi query(int l, int r, int ql, int qr, int i)
  {
    int mid = (l + r) >> 1;
    if (l > r || l > qr || r < ql)
      return {0, 0};
    if (l >= ql && r <= qr)
      return {seg[i], r - l + 1};
    pi a = query(l, mid, ql, qr, i << 1);
    pi b = query(mid + 1, r, ql, qr, (i << 1) | 1);
    return {merge(a.fir, a.sec, b.fir, b.sec), a.sec + b.sec};
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      seg[i] = s[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
    seg[i] = merge(seg[i << 1], mid - l + 1, seg[(i << 1) | 1], r - (mid + 1) + 1);
  }
  void init(string t)
  {
    s = t;
    seg.resize(4 * s.size());
    build(0, s.size() - 1, 1);
  }
  int get(int l, int r)
  {
    return query(0, s.size() - 1, l, r, 1).fir;
  }
  void upd(int i, int c)
  {
    update(1, 0, s.size() - 1, i, c);
  }
};
int append(int a, int al, int b, int bl)
{
  a = sum(multiplicate(a, pot[bl]), b);
  return a;
}
void calc()
{
  pot[0] = 1;
  for (int i = 1; i < MAXN; i++)
    pot[i] = multiplicate(pot[i - 1], d);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  int n, q;
  cin >> n >> q;
  vector<string> vv(n);
  vector<pair<seg, seg>> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> vv[i];
    v[i].fir.init(vv[i]);
    reverse(vv[i].begin(), vv[i].end());
    v[i].sec.init(vv[i]);
    reverse(vv[i].begin(), vv[i].end());
  }
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int i, j;
      char c;
      cin >> i >> j >> c;
      i--, j--;
      v[i].fir.upd(j, c);
      v[i].sec.upd((vv[i].size() - 1) - j, c);
    }
    else if (t == 2)
    {
      int i, j, l1, r1, l2, r2;
      cin >> i >> j >> l1 >> r1 >> l2 >> r2;
      i--, j--, l1--, r1--, l2--, r2--;
      if (v[i].fir.get(l1, r1) == v[j].fir.get(l2, r2))
        cout << "equal\n";
      else
        cout << "different\n";
    }
    else
    {
      int i, j, l1, r1, l2, r2;
      cin >> i >> j >> l1 >> r1 >> l2 >> r2;
      i--, j--, l1--, r1--, l2--, r2--;
      int sz = (vv[i].size() - 1), sz2 = (vv[j].size() - 1);
      int s1 = append(v[i].fir.get(l1, r1), r1 - l1 + 1, v[j].fir.get(l2, r2), r2 - l2 + 1);
      int s2 = append(v[j].sec.get(sz2 - r2, sz2 - l2), r2 - l2 + 1, v[i].sec.get(sz - r1, sz - l1), r1 - l1 + 1);
      if (s1 == s2)
        cout << "cool\n";
      else
        cout << "not so cool\n";
    }
  }
}
// abc + de
// edcba