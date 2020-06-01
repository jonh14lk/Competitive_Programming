#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 101
#define MAXL 20
#define mod 998244353

int n, m;
int bit[MAXN][MAXN];
int grid[MAXN][MAXN];

int sum(int x, int y)
{
  int ret = 0;
  for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
    for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
      ret += bit[i][j];
  return ret;
}
void add(int x, int y, int delta)
{
  for (int i = x; i < n; i = i | (i + 1))
    for (int j = y; j < m; j = j | (j + 1))
      bit[i][j] += delta;
}
signed main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> grid[i][j], add(i, j, grid[i][j]);
  int q;
  cin >> q;
  while (q--)
  {
    char t;
    cin >> t;
    if (t == 'Q') // query
    {
      int a, b;
      cin >> a >> b;
      cout << sum(a, b) << endl;
      // soma de todas as posicoes (x,y) tal que, (0 <= x <= a) e (0 <= y <= b)
    }
    else // update
    {
      int a, b, c;
      cin >> a >> b >> c;
      add(a, b, c - grid[a][b]);
    }
  }
  return 0;
}
