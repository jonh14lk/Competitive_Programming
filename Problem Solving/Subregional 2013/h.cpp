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
#define MAXN 2000
#define mod 1000000

namespace matrix
{
  vector<vector<int>> ans;

  int mul(int x, int y)
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
          res[i][j] = sum(res[i][j], mul(a[i][k], b[k][j]));
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
    while (m)
    {
      if (m & 1)
        ans = multiply(ans, mat);
      m = m >> 1;
      mat = multiply(mat, mat);
    }
    return ans;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k, l;
  cin >> n >> k >> l;
  n /= 5;
  k %= mod;
  l %= mod;
  vector<vector<int>> a = {{k, l},
                           {1, 0}};
  vector<vector<int>> b = {{k}, {1}};
  a = matrix::expo(a, n - 1);
  a = matrix::multiply(a, b);
  string ans = to_string(a[0][0]);
  while (ans.size() < 6)
    ans = "0" + ans;
  cout << ans << endl;
  return 0;
}
// dividir n por 5
// 1 2 3 5 8 13 21
// fibonacci para n 1 1
// recorrencia
// a[0] = 1
// a[1] = k
// a[i] = k * a[i - 1] + l * a[i - 2]