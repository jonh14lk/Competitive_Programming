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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

namespace matrix
{
  vector<vector<int>> ans;

  int multi(int x, int y)
  {
    return (x * y) % mod;
  }
  int sum(int a, int b)
  {
    return (a + b >= mod) ? a + b - mod : a + b;
  }
  vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b)
  {
    vector<vector<int>> res(a[0].size(), vector<int>(b[0].size()));
    for (int i = 0; i < a.size(); i++)
    {
      for (int j = 0; j < b[0].size(); j++)
      {
        res[i][j] = 0;
        for (int k = 0; k < a[0].size(); k++)
          res[i][j] = sum(res[i][j], multi(a[i][k], b[k][j]));
      }
    }
    return res;
  }
  vector<vector<int>> expo(vector<vector<int>> mat, int m)
  {
    ans = vector<vector<int>>(mat.size(), vector<int>(mat[0].size()));
    for (int i = 0; i < mat.size(); i++)
      for (int j = 0; j < mat[0].size(); j++)
        ans[i][j] = (i == j);
    while (m > 0)
    {
      if (m & 1)
        ans = multiply(ans, mat);
      m = m / 2;
      mat = multiply(mat, mat);
    }
    return ans;
  }
}

vector<vector<int>> x[61];
vector<vector<int>> y[61];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<pi> v(m);
  int max_a = 0;
  for (int i = 0; i < m; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    max_a = max(max_a, v[i].fir);
  }
  for (int h = 0; h <= 60; h++)
  {
    x[h] = vector<vector<int>>(max_a + 1, vector<int>(max_a + 1, 0));
    for (int el = 1; el <= max_a; el++)
    {
      x[h][el][el - 1]++;
    }
  }
  for (auto [a, b] : v)
  {
    for (int h = b; h <= 60; h++)
      x[h][0][a - 1]++;
  }
  y[0] = vector<vector<int>>(max_a + 1, vector<int>(max_a + 1, 0));
  for (int i = 0; i <= max_a; i++)
  {
    for (int j = 0; j <= max_a; j++)
      y[0][i][j] = (i == j);
  }
  for (int h = 1; h <= 60; h++)
  {
    y[h] = matrix::multiply(matrix::multiply(y[h - 1], x[h - 1]), y[h - 1]);
  }
  vector<vector<int>> res = vector<vector<int>>(max_a + 1, vector<int>(max_a + 1, 0));
  for (int i = 0; i <= max_a; i++)
  {
    for (int j = 0; j <= max_a; j++)
      res[i][j] = (i == j);
  }
  for (int h = 0; h <= 60; h++)
  {
    if (n & (1ll << h))
    {
      res = matrix::multiply(res, x[h]);
      res = matrix::multiply(res, y[h]);
    }
  }
  vector<vector<int>> mat;
  for (int i = 0; i <= max_a; i++)
  {
    mat.pb({(i == 0)});
  }
  mat = matrix::multiply(res, mat);
  cout << mat[0][0] << endl;
}