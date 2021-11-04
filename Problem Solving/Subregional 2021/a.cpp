#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 5005
#define mod 1000000007
#define debug if (1)

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
modint fat[MAXN];
modint inv_fat[MAXN];
void calc()
{
  fat[0] = 1;
  inv_fat[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    fat[i] = fat[i - 1] * i;
    inv_fat[i] = fat[i].inv();
  }
}
struct lagrange
{
  vector<modint> den;
  vector<modint> y;

  lagrange(vector<modint> &v) // f(i) = v[i], gera um polinomio de grau n - 1
  {
    int n = v.size();
    den.resize(n);
    y.resize(n);
    for (int i = 0; i < n; i++)
    {
      y[i] = v[i];
      den[i] = inv_fat[n - i - 1] * inv_fat[i];
      if ((n - i - 1) % 2 == 1)
      {
        int x = (mod - den[i].val) % mod;
        den[i] = x;
      }
    }
  }
  modint get_val(int x) // complexity: O(n)
  {
    x %= mod;
    int n = y.size();
    vector<modint> l(n);
    vector<modint> r(n);
    l[0] = 1, r[n - 1] = 1;
    for (int i = 1; i < n; i++)
    {
      modint cof = (x - (i - 1) + mod);
      l[i] = l[i - 1] * cof;
    }
    for (int i = n - 2; i >= 0; i--)
    {
      modint cof = (x - (i + 1) + mod);
      r[i] = r[i + 1] * cof;
    }
    modint ans = 0;
    for (int i = 0; i < n; i++)
    {
      modint cof = l[i] * r[i];
      ans += modint(cof * y[i]) * den[i];
    }
    return ans;
  }
};

int n, r;
vector<int> v;
modint dp[MAXN][MAXN];

void solve()
{
  calc();
  for (int j = 0; j <= n; j++)
    dp[n][j] = 1;
  for (int i = n - 1; i >= 0; i--)
  {
    // acha os n + 1 primeiros valores do polinomio
    // Q(x) = Σ dp[i + 1][j]
    vector<modint> y;
    y.pb(dp[i + 1][0]);
    for (int j = 1; j <= n; j++)
    {
      dp[i + 1][j] += dp[i + 1][j - 1];
      y.pb(dp[i + 1][j]);
    }
    // precisamos achar o valor de Q(v[i] - 1)
    // dai da pra fazer interpolando já que a gente tem
    // os n + 1 primeiros valores
    // além disso, precisamos manter na dp os ultimos n + 1 valores
    // pro polinomio
    // isso eh: dp[r - n], ..., dp[r - 1], dp[r]
    lagrange l(y);
    if (n == n - 1) // faz o shift pros ultimos n + 1 valores, terminando em r
    {
      // antes: dp[0] = dp[0], ... dp[n] = dp[n]
      modint x = l.get_val(v[i] - 1);
      for (int j = 0, k = r - n; j <= n; j++, r++)
      {
        // dp[i][j] = Q(k) - Q(v[i] - 1)
        modint kappa = l.get_val(k);
        kappa -= x;
        dp[i][j] = kappa;
      }
      // ao final: dp[0] = dp[r - n], ... dp[n] = dp[r]
    }
    else // ja foi shiftado pro final
    {
      int dif = r - (v[i] - 1);
      dif = n - dif;
      modint x = l.get_val(dif);
      for (int j = 0; j <= n; j++)
      {
        // dp[i][j] = Q(k) - Q(v[i] - 1)
        modint kappa = dp[i + 1][j];
        kappa -= x;
        dp[i][j] = kappa;
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> r;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int mx = -1;
  for (int i = n - 1; i >= 0; i--)
  {
    mx = max(mx, v[i]);
    v[i] = mx;
  }
  if (mx > r)
  {
    cout << 0 << endl;
    return 0;
  }
  solve();
  cout << dp[0][n].val << endl;
  return 0;
}
