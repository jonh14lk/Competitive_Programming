#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 3001

bool can;
int matrix[MAXN][MAXN];
bool matrix2[MAXN][MAXN];
bool matrix3[MAXN][MAXN];

void ans(int i, int j, int l, int n, int k)
{
  if (i == n && j == n + 1 && l == k && can)
  {
    cout << "POSSIBLE\n";
    for (int a = 1; a <= n; a++)
    {
      for (int b = 1; b <= n; b++)
      {
        cout << matrix[a][b] << " ";
      }
      cout << endl;
    }
    can = false;
    return;
  }
  else if (i > n)
  {
    return;
  }
  else if (j > n)
  {
    ans(i + 1, 1, l, n, k);
  }
  for (int a = 1; a <= n && can; a++)
  {
    if (!matrix2[i][a] && !matrix3[j][a])
    {
      matrix2[i][a] = true;
      matrix3[j][a] = true;
      if (i == j)
      {
        l += a;
      }
      matrix[i][j] = a;
      ans(i, j + 1, l, n, k);
      matrix2[i][a] = false;
      matrix3[j][a] = false;
      if (i == j)
      {
        l -= a;
      }
      matrix[i][j] = 0;
    }
  }
}
signed main()
{
  int q;
  cin >> q;
  for (int c = 1; c <= q; c++)
  {
    cout << "Case #" << c << ": ";
    int n, k;
    cin >> n >> k;
    can = true;
    ans(1, 1, 0, n, k);
    if (can)
    {
      cout << "IMPOSSIBLE\n";
    }
  }
}