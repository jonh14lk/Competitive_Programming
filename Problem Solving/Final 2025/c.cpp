#include <bits/stdc++.h>
using namespace std;

#define int __int128
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

__int128 read()
{
  __int128 x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(__int128 x)
{
  if (x < 0)
  {
    cout << "-";
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  char at = (x % 10) + '0';
  cout << at;
}

const int inf = 1e18;

struct fraction
{
  int x, y; // x / y

  fraction() {}
  fraction(int x, int y) : x(x), y(y) {}
  const bool operator!=(const fraction &o) const { return (x * o.y != o.x * y); }
  const bool operator<(const fraction &o) const { return (x * o.y < o.x * y); }
  fraction operator+(fraction o)
  {
    fraction ans;
    ans.y = (y == o.y) ? y : y * o.y;
    ans.x = (x) * (ans.y / y) + (o.x) * (ans.y / o.y);
    ans.simplify();
    return ans;
  }
  fraction operator*(fraction o)
  {
    fraction ans;
    ans.x = x * o.x;
    ans.y = y * o.y;
    ans.simplify();
    return ans;
  }
  void simplify()
  {
    int g = __gcd(y, x);
    x /= g;
    y /= g;
  }
};
struct segtree
{
  int n;
  vector<int> seg;

  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a + b;
  }
  segtree(int sz)
  {
    n = 1;
    while (n < sz)
      n <<= 1;
    seg.assign(n << 1, neutral());
  }
  void upd(int i, int value)
  {
    seg[i] = merge(seg[i += n], value);
    for (i >>= 1; i; i >>= 1)
      seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r)
  {
    if (l > r)
      return 0;
    int ansl = neutral(), ansr = neutral();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
        ansl = merge(ansl, seg[l++]);
      if (r & 1)
        ansr = merge(seg[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, s, k;
  n = read();
  s = read();
  k = read();
  vector<pii> v(n);
  for (int i = 0; i < n; i++)
  {
    v[i].fir = read();
    v[i].sec.fir = read();
    v[i].sec.sec = read();
  }
  sort(v.begin(), v.end());
  int id = 0;
  vector<int> h(n);
  vector<int> l(n);
  vector<int> r(n);
  vector<pair<fraction, pi>> ev;
  for (auto const &i : v)
  {
    h[id] = i.fir;
    l[id] = i.sec.fir;
    r[id] = i.sec.sec;
    ev.pb({fraction(l[id], h[id]), {0, id}});
    ev.pb({fraction(r[id], h[id]), {1, id}});
    id++;
  }
  sort(ev.begin(), ev.end());
  fraction ans(inf, 1);
  int sum = 0;
  segtree st(n);
  segtree st2(n);
  for (int i = 0; i < ev.size(); i++)
  {
    int id = ev[i].sec.sec;
    int a = ev[i].fir.x, b = ev[i].fir.y;
    // (p_i / h_i) = (a / b)
    // p_i = (a / b) * h_i
    // quero computar s_i * (a / b) * h_i
    if (ev[i].sec.fir == 0)
    {
      sum += (k / h[id]);
      st.upd(id, (k / h[id]));
      st2.upd(id, (k / h[id]) * h[id]);
      if (sum >= s)
      {
        int l = 0, r = n - 1;
        while (l < r)
        {
          int mid = (l + r) >> 1;
          (st.qry(0, mid) >= s) ? r = mid : l = mid + 1;
        }
        int curr = st2.qry(0, l - 1);
        curr += h[l] * (s - st.qry(0, l - 1));
        fraction tot(curr, 1);
        tot = tot * ev[i].fir;
        if (tot < ans)
        {
          ans = tot;
        }
      }
    }
    else
    {
      sum -= (k / h[id]);
      st.upd(id, -(k / h[id]));
      st2.upd(id, -((k / h[id]) * h[id]));
    }
  }
  if (ans.x == inf)
  {
    cout << "*\n";
  }
  else
  {
    int g = __gcd(ans.x, ans.y);
    ans.x /= g;
    ans.y /= g;
    print(ans.x);
    cout << " ";
    print(ans.y);
    cout << endl;
  }
  return 0;
}