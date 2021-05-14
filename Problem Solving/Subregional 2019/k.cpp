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
#define MAXN 403
#define mod 1000000007
#define INF 1e7

namespace matrix
{
  int multi(int x, int y)
  {
    return (x * y) % mod;
  }
  int sum(int a, int b)
  {
    return (a + b) % mod;
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
    vector<vector<int>> ans(mat.size(), vector<int>(mat[0].size()));
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
} // namespace matrix
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  if (n == 1)
  {
    cout << 2 << endl;
    return 0;
  }
  if (n == 2)
  {
    cout << 24 << endl;
    return 0;
  }
  vector<vector<int>> mat(4, vector<int>(4, 0));
  vector<vector<int>> mat2(4, vector<int>(1, 0));
  mat[0][0] = 2;
  mat[0][1] = 4;
  mat[0][3] = 2;
  mat[1][0] = 1;
  mat[2][1] = 4;
  mat[2][2] = 2;
  mat[3][3] = 2;
  mat2[0][0] = 12;
  mat2[1][0] = 2;
  mat2[3][0] = 4;
  vector<vector<int>> ans = matrix::expo(mat, n - 2);
  ans = matrix::multiply(ans, mat2);
  cout << ((((2 * ans[0][0]) % mod) + ((2 * ans[2][0]) % mod)) % mod) << endl;
}
// se começamos na coluna i, primeiro temos que passar por todas as posições
// a esquerda de i, em seguida voltar para a coluna i e em seguida passar
// pelas posições a direita de i.
// f(n) -> numero de caminhos que começam da primeira coluna
// t(n) -> numero de caminhos no qual posso começar em qualquer lugar
// g(n) -> 2^n
// f(n) = 2 * f(n - 1) + 4 * f(n - 2) + 0 * t(n - 1) + 2 * g(n - 1)
// t(n) = 0 * f(n - 1) + 4 * f(n - 2) + 2 * t(n - 1) + 0 * g(n - 1)
// com isso, podemos escrever a resposta final como:
// 2 * f(n) + 2 * t(n)
// valores base:
// f(2) == 12
// f(1) == 2
// t(2) == 0
// g(2) == 4