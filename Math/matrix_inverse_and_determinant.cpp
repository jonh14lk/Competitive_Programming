#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

struct modint
{
  int val;
  modint(int v = 0) { val = (v + mod) % mod; }
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
pair<int, modint> gauss(vector<vector<modint>> &a, int pivot_end)
{
  int n = a.size(), m = a[0].size();
  int rank = 0, curr = pivot_end;
  if (curr == -1)
    curr = m;
  modint det = 1;
  for (int j = 0; j < curr; j++)
  {
    int idx = -1;
    for (int i = rank; i < n; i++)
    {
      if (a[i][j].val != 0)
      {
        idx = i;
        break;
      }
    }
    if (idx == -1)
    {
      det = 0;
      continue;
    }
    if (rank != idx)
    {
      det *= -1;
      swap(a[rank], a[idx]);
    }
    det *= a[rank][j];
    if (a[rank][j].val != 1)
    {
      modint coef = a[rank][j].inv();
      for (int k = j; k < m; k++)
        a[rank][k] *= coef;
    }
    int is = 0;
    for (int i = is; i < n; i++)
    {
      if (i == rank)
        continue;
      if (a[i][j].val != 0)
      {
        modint coef = a[i][j] / a[rank][j];
        for (int k = j; k < m; k++)
          a[i][k] -= a[rank][k] * coef;
      }
    }
    rank++;
  }
  return {rank, det};
}
vector<vector<modint>> inverse_matrix(vector<vector<modint>> a)
{
  int n = a.size();
  vector<vector<modint>> m(n, vector<modint>(2 * n));
  for (int i = 0; i < n; i++)
  {
    copy(begin(a[i]), end(a[i]), begin(m[i]));
    m[i][n + i] = 1;
  }
  auto [rank, det] = gauss(m, n);
  if (rank != n)
    return {};
  vector<vector<modint>> b(n);
  for (int i = 0; i < n; i++)
    copy(begin(m[i]) + n, end(m[i]), back_inserter(b[i]));
  return b;
}
modint determinant(vector<vector<modint>> a)
{
  return gauss(a, -1).sec;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<vector<modint>> v(n, vector<modint>(n));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cin >> v[i][j].val;
  }
  if (determinant(v).val == 0)
  {
    cout << "-1\n";
    return 0;
  }
  vector<vector<modint>> ans = inverse_matrix(v);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << ans[i][j].val << " ";
    cout << endl;
  }
  return 0;
}
// https://judge.yosupo.jp/problem/inverse_matrix
// https://judge.yosupo.jp/problem/matrix_det
// como precisa de divisão, então o mod tem que ser primo