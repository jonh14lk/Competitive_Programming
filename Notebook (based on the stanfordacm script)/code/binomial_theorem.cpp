#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma gcc optimize("Ofast")

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct modint
{
  int val;
  modint(int v = 0) { val = (v < 0) ? v + mod : v; }
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
modint invfat[MAXN];

void calc()
{
  f[0] = 1;
  for (int i = 1; i < MAXN; i++)
    f[i] = f[i - 1] * i;
  for (int i = 0; i < MAXN; i++)
    invfat[i] = f[i].inv();
}
modint ncr(int n, int k)
{
  modint ans = f[n] * invfat[k];
  ans *= invfat[n - k];
  return ans;
}

struct strange_modint // escrever um numero na forma: a + (b * sqrt(5))
{
  modint a, b;
  strange_modint() { a = 0, b = 0; }
  strange_modint(modint v) { a = v, b = 0; }
  strange_modint(modint v, modint v2) { a = v, b = v2; }
  strange_modint operator*(strange_modint o)
  {
    return strange_modint((a * o.a) + (b * o.b * 5), (a * o.b) + (b * o.a));
  }
  strange_modint operator+(strange_modint o)
  {
    return strange_modint(a + o.a, b + o.b);
  }
  strange_modint operator-(strange_modint o)
  {
    return strange_modint(a - o.a, b - o.b);
  }
  strange_modint pow(int y)
  {
    strange_modint x(a, b);
    strange_modint z(1, 0);
    while (y)
    {
      if (y & 1)
        z = z * x;
      x = x * x;
      y >>= 1;
    }
    return z;
  }
};

strange_modint matrix_ans[3][3];

void matrix_multiply(strange_modint a[3][3], strange_modint b[3][3])
{
  strange_modint res[3][3];
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
        res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
    }
  }
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      a[i][j] = res[i][j];
  }
}
void matrix_pow(strange_modint mat[3][3], int m)
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
      matrix_ans[i][j] = strange_modint((i == j));
  }
  while (m > 0)
  {
    if (m & 1)
      matrix_multiply(matrix_ans, mat);
    m = m / 2;
    matrix_multiply(mat, mat);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  int n, k;
  cin >> n >> k;
  strange_modint a(modint(1) / 2, modint(1) / 2);
  strange_modint b(modint(1) / 2, -(modint(1) / 2));
  strange_modint c(0, modint(1) / 5);
  strange_modint ans(0, 0);
  for (int j = 0; j <= k; j++)
  {
    strange_modint curr(modint(1000000006).pow(j), 0); // (-1)^j
    curr = curr * strange_modint(ncr(k, j), 0);
    strange_modint prod = a.pow(k - j) * b.pow(j);
    strange_modint s0(0, 0);
    strange_modint s1(1, 0);
    strange_modint mat[3][3] = {{prod, s0, s1}, {s1, s0, s0}, {s0, s0, s1}};
    matrix_pow(mat, n);
    curr = curr * (matrix_ans[0][0] + matrix_ans[0][2]);
    ans = ans + curr;
  }
  ans = ans * c.pow(k);
  cout << ans.a.val << endl;
  return 0;
}
// https://codeforces.com/gym/104412/problem/F