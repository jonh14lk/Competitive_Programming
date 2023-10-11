#include <bits/stdc++.h>

using namespace std;

#define int long long int

int n;
int d[101][101][102], t[101][101][102], m[101][101];

void floyd()
{
  for (int k = 0; k < n; k++)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        int new_dist = d[i][k][k] + d[k][j][k];
        if (new_dist < d[i][j][k])
        {
          d[i][j][k + 1] = new_dist;
          t[i][j][k + 1] = t[i][k][k] + t[k][j][k];
        }
        else if (new_dist == d[i][j][k])
        {
          d[i][j][k + 1] = d[i][j][k];
          t[i][j][k + 1] = max(t[i][j][k], t[i][k][k] + t[k][j][k]);
        }
        else
        {
          d[i][j][k + 1] = d[i][j][k];
          t[i][j][k + 1] = t[i][j][k];
        }
      }
    }
  }
}

signed main()
{
  cin >> n;
  for (int k = 0; k <= n; k++)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        d[i][j][k] = 1e18;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> m[i][j];
      t[i][j][0] = (i != j);
      d[i][j][0] = m[i][j];
    }
  }

  floyd();
  int cnt = 0;

  // checar se eh incoerente
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i == j)
        continue;
      if (d[i][j][n] < m[i][j])
      {
        cout << -1 << endl;
        return 0;
      }
      else if (d[i][j][n] == m[i][j] && t[i][j][n] > 1)
      {
        cnt++;
      }
    }
  }
  cout << cnt / 2 << endl;
}