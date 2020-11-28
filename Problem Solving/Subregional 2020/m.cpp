#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<double, double>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007
#define eps -0.000000001

int pot[MAXN];
vector<pi> seg[4 * MAXN];
vector<int> curr;
vector<pii> v;

int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int sum(int x, int y)
{
  return (x + y) % mod;
}
pi rotate(pi p)
{
  p.sec = p.sec * 2;
  double a = (45 * PI) / 180;
  pi ans;
  ans.fir = (cos(a) * p.fir) + ((sin(a) * -1) * p.sec);
  ans.sec = (sin(a) * p.fir) + (cos(a) * p.sec);
  return ans;
}
void query(int l, int r, int ql, int qr, int i, double x)
{
  int mid = (l + r) >> 1;
  if (l > r || l > qr || r < ql)
  {
    return;
  }
  if (l >= ql && r <= qr)
  {
    for (int j = seg[i].size() - 1; j >= 0; j--)
    {
      if (seg[i][j].fir - x >= eps)
        curr.pb(seg[i][j].sec);
      else
        break;
    }
    return;
  }
  query(l, mid, ql, qr, i << 1, x);
  query(mid + 1, r, ql, qr, (i << 1) | 1, x);
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i].pb({v[l].fir.sec, v[l].sec});
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  merge(seg[i << 1].begin(), seg[i << 1].end(), seg[(i << 1) | 1].begin(), seg[(i << 1) | 1].end(), back_inserter(seg[i]));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  v.resize(n);
  pot[0] = 1;
  for (int i = 1; i <= n; i++)
    pot[i] = multiplicate(pot[i - 1], 5782344);
  for (int i = 0; i < n; i++)
  {
    pi k;
    cin >> k.fir >> k.sec;
    k = rotate(k);
    v[i] = {k, i + 1};
  }
  sort(v.begin(), v.end());
  build(0, n - 1, 1);
  int p = 0, c = 0;
  for (int i = 0; i < q; i++)
  {
    int a, b;
    cin >> a >> b;
    pi k = rotate({-1 - sum(p, a), sum(p, b)});
    int l = 0, r = n - 1;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      (v[mid].fir.fir - k.fir >= eps) ? r = mid : l = mid + 1;
    }
    curr.clear();
    if (v[l].fir.fir - k.fir >= eps)
    {
      query(0, n - 1, l, n - 1, 1, k.sec);
      sort(curr.begin(), curr.end());
    }
    p = 0, c = 0;
    for (auto const &i : curr)
    {
      p = sum(p, multiplicate(i, pot[c]));
      c++;
    }
    cout << p << endl;
  }
  return 0;
}
// 1000000
// 5568085
