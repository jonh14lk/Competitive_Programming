#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1001
#define mod 1000000007

struct modint
{
  int val;
  modint(int v = 0) { val = v % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

modint f[MAXN];
modint inv[MAXN];
modint invfat[MAXN];

int n, qt;
int ll[MAXN];
int rr[MAXN];
bool cover[MAXN][MAXN];
int dp[MAXN][MAXN];
modint prec_ncr[MAXN][MAXN];

modint ncr(int n, int k)
{
  if (k > n)
    return 0;
  modint num = 1;
  modint den = 1;
  for (int i = 0; i < k; i++)
  {
    num = num * modint(n - i);
    den = den * modint(i + 1);
  }
  modint ans = num / den;
  return ans;
}
int solve(int i, int j)
{
  if (j == n)
    return 1;
  if (i == qt)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  modint ans = solve(i + 1, j);
  for (int k = j; k < n; k++)
  {
    if (!cover[i][k])
      break;
    modint ways = prec_ncr[i][k - j + 1];
    ways *= solve(i + 1, k + 1);
    ans += ways;
  }
  return dp[i][j] = ans.val;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  vector<pi> v(n);
  vector<int> pts;
  for (int i = 0; i < n; i++)
  {
    int l, r;
    cin >> l >> r;
    v[i] = {l, r};
    pts.pb(l);
    pts.pb(r + 1);
  }
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  for (int i = 0; (i + 1) < pts.size(); i++)
  {
    int l = pts[i], r = pts[i + 1] - 1;
    vector<bool> at(n, 0);
    for (int j = 0; j < n; j++)
    {
      if (v[j].fir <= l && r <= v[j].sec)
        at[j] = 1;
    }
    bool same = 0;
    if (i > 0 && (rr[qt - 1] + 1) == l)
      same = 1;
    for (int j = 0; j < n && same; j++)
    {
      if (cover[qt - 1][j] != at[j])
        same = 0;
    }
    if (same)
    {
      rr[qt - 1] = r;
      continue;
    }
    for (int j = 0; j < n; j++)
      cover[qt][j] = at[j];
    ll[qt] = l;
    rr[qt] = r;
    qt++;
  }
  for (int i = 0; i < qt; i++)
  {
    int len = rr[i] - ll[i] + 1;
    for (int j = 1; j <= n; j++)
      prec_ncr[i][j] = ncr(len, j);
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0, 0) << endl;
  return 0;
}
