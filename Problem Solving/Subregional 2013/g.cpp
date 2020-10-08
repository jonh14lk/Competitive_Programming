#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define double long double
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 301
#define MAXL 20
#define mod 998244353

int ans;
int grid[MAXN][MAXN];

void swap_lines(int a, int b, int n)
{
  for (int i = 0; i < n; i++)
    swap(grid[a][i], grid[b][i]);
}
void swap_cols(int a, int b, int n)
{
  for (int i = 0; i < n; i++)
    swap(grid[i][a], grid[i][b]);
}
void my_sort(int n, int arr[], int m)
{
  while (n > 1)
  {
    int big = 0;
    for (int i = 0; i < n; i++)
      if (arr[i] > arr[big])
        big = i;
    if (big != n - 1)
      ans++, swap(arr[n - 1], arr[big]), swap_lines(n - 1, big, m);
    n--;
  }
}
void my_sort2(int n, int arr[], int m)
{
  while (n > 1)
  {
    int big = 0;
    for (int i = 0; i < n; i++)
      if (arr[i] > arr[big])
        big = i;
    if (big != n - 1)
      ans++, swap(arr[n - 1], arr[big]), swap_cols(n - 1, big, m);
    n--;
  }
}
signed main()
{
  int n, m, at = 1;
  cin >> n >> m;
  int line[m], col[n];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> grid[i][j];
  for (int i = 0; i < n; i++)
    col[i] = grid[i][0];
  for (int i = 0; i < m; i++)
    line[i] = grid[0][i];
  my_sort(n, col, m);
  my_sort2(m, line, n);
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (grid[i][j] != at)
      {
        cout << "*\n";
        return 0;
      }
      at++;
    }
  }
  cout << ans << endl;
  return 0;
}