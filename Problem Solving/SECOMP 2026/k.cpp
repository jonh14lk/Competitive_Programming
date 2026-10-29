
#include <bits/stdc++.h>
using namespace std;

#define int long long int

int a[101][101];
int g[101][101];
int linha[101];
int coluna[101];

signed main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
  }
  int all_sum = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> g[i][j];
      if (g[i][j] == 2)
      {
        a[i][j] *= -1;
      }
      linha[i] += a[i][j];
      coluna[j] += a[i][j];
      all_sum += a[i][j];
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (all_sum == 2 * linha[i])
    {
      cout << "1 " << i + 1 << endl;
      return 0;
    }
    if (all_sum == 2 * coluna[i])
    {
      cout << "2 " << i + 1 << endl;
      return 0;
    }
  }
}