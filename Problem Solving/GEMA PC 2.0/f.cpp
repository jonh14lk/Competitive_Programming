#include <bits/stdc++.h>
using namespace std;

#define DEBUG(X) if (X)
#define pb push_back
typedef long long int lli;
typedef vector<lli> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<vector<ii>> vvii;

int mat[50][50];
int second[50][50];

void go(int n, int m, int r, int s)
{
  int qnt = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (i + r <= n && j + s <= m)
      {
        int count = 1;
        for (int k = 0; k < r; k++)
        {
          for (int w = 0; w < s; w++)
          {
            // printf("i = %d, j = %d, k = %d, w = %d\n", i, j, k, w);
            if (mat[i + k][j + w] != second[k][w])
            {
              count = 0;
              break;
            }
          }
        }
        qnt += count;
      }
    }
  }
  cout << qnt << endl;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> mat[i][j];
  int l, r;
  cin >> l >> r;

  for (int i = 0; i < l; i++)
    for (int j = 0; j < r; j++)
      cin >> second[i][j];
  go(n, m, l, r);
  return 0;
}