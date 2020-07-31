// https://codeforces.com/gym/102644/problem/C
// achar o n-ésimo termo da sequencia de fibonacci mod (10^9 + 7) em O(log(n))
// n <= 10^18
// podemos escrever a recorrencia de fibonnaci como uma exponenciação de matriz
/*
  (  fib(n)  )      (1 1) ^ (n - 1)      (fib(1) = 1)
  (fib(n - 1))   =  (1 0)             *  (fib(0) = 1)
*/
// é possivel fazer essa exponenciação em O(log(n)) com um algoritimo muito similar ao de exponenciação rapida
// dai calculamos o n-ésimo termo da sequencia de fibonacci mod (10^9 + 7) em O(log(n))

#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define int long long int
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 20
#define INF 200001
#define mod 1000000007

const int n = 2;
vector<vector<int>> ans(n, vector<int>(n));

vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b)
{
  vector<vector<int>> res(n, vector<int>(n));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      res[i][j] = 0;
      for (int k = 0; k < n; k++)
        res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
    }
  }
  return res;
}
vector<vector<int>> expo(vector<vector<int>> mat, int m)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
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
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int m;
  cin >> m;
  vector<vector<int>> mat = {{1, 1}, {1, 0}};
  vector<vector<int>> ans = expo(mat, m - 1);
  cout << ans[0][0] + ans[0][1] << endl;
  return 0;
}
