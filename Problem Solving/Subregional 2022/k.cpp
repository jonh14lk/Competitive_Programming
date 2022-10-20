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
#define MAXN 100005
#define mod 1000000000

struct modint
{
  int val;
  modint(int v = 0) { val = v; }
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
struct poly
{
  modint p[402];
  poly() {}
  poly(int x) { p[0] = 1; }
  poly operator+(poly ot)
  {
    poly ans = poly();
    for (int i = 0; i < 402; i++)
      ans.p[i] = p[i] + ot.p[i];
    return ans;
  }
  poly operator*(poly ot)
  {
    poly ans = poly();
    for (int i = 0; i < 402; i++)
    {
      for (int j = 0; i + j < 402; j++)
        ans.p[i + j] += (p[i] * ot.p[j]);
    }
    return ans;
  }
};

int n, m, k;
int coef[12][402];
poly c[11];

namespace matrix
{
  vector<vector<poly>> ans;

  vector<vector<poly>> multiply(vector<vector<poly>> a, vector<vector<poly>> b)
  {
    vector<vector<poly>> res(a.size(), vector<poly>(b[0].size()));
    for (int i = 0; i < a.size(); i++)
    {
      for (int j = 0; j < b[0].size(); j++)
      {
        res[i][j] = poly();
        for (int k = 0; k < a[0].size(); k++)
          res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
      }
    }
    return res;
  }
  vector<vector<poly>> expo(vector<vector<poly>> mat, int m)
  {
    bool ini = 0;
    while (m > 0)
    {
      if (m & 1)
      {
        if (!ini)
          ans = mat;
        else
          ans = multiply(ans, mat);
        ini = 1;
      }
      m = m / 2;
      mat = multiply(mat, mat);
    }
    return ans;
  }
}
vector<vector<poly>> naive()
{
  vector<vector<int>> dp(12, vector<int>(k + 1, 0));
  dp[0][0] = 1;
  for (int i = 1; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      if (i - j >= 0)
      {
        for (int x = 0; x <= k; x++)
        {
          for (int y = 0; y <= k; y++)
          {
            if (x + y <= k)
            {
              dp[i][x + y] += (dp[i - j][x] * coef[j][y]) % mod;
              dp[i][x + y] % mod;
            }
          }
        }
      }
    }
  }
  vector<vector<poly>> ans;
  for (int i = 0; i < 12; i++)
  {
    poly aux = poly();
    for (int x = 0; x <= k; x++)
      aux.p[x] = dp[i][x];
    ans.pb({aux});
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++)
  {
    int d, p;
    cin >> d >> p;
    coef[d][p]++;
    c[d].p[p] += 1;
  }
  vector<vector<poly>> ini = naive();
  if (n <= 12)
  {
    modint tot = 0;
    for (int x = 0; x <= k; x++)
      tot += ini[n - 1][0].p[x];
    cout << tot.val << endl;
    return 0;
  }
  vector<vector<poly>> mat(12, vector<poly>(12));
  for (int i = 0; i < 11; i++)
  {
    mat[i][i + 1] = poly(1);
  }
  for (int i = 1; i <= 10; i++)
  {
    mat[11][11 - i + 1] = c[i];
  }
  vector<vector<poly>> ans = matrix::expo(mat, n - 12);
  vector<vector<poly>> aa = matrix::multiply(ans, ini);
  modint tot = 0;
  for (int x = 0; x <= k; x++)
    tot += aa[11][0].p[x];
  cout << tot.val << endl;
  return 0;
}
// escrever a dp naive

// pensando em resolver o problema sem a parte de energia
// da pra resolver com recorrencia linear e exponenciação de matriz
// ve os valores iniciais

// o problema eh como lidar com a restrição de energia?
// cada elemento da matriz sendo um polinomio de grau k