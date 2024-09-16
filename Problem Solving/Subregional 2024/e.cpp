#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;

  cin >> n;

  int m[n][n];

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> m[i][j];
    }
  }

  int resp = 0, v = m[0][0];

  if (m[0][n - 1] < v)
  {
    v = m[0][n - 1];
    resp = 1;
  }

  if (m[n - 1][n - 1] < v)
  {
    v = m[n - 1][n - 1];
    resp = 2;
  }

  if (m[n - 1][0] < v)
  {
    v = m[n - 1][0];
    resp = 3;
  }

  cout << resp << endl;

  return 0;
}