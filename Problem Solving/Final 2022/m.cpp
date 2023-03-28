#include <bits/stdc++.h>
using namespace std;

#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define pb push_back

int n, m;
string s;
string t[1001];
bool can[1001][101];
bool vis[1001][101];

void dfs(int i, int j)
{
  vis[i][j] = 1;
  if (i + 1 < n && !vis[i + 1][j] && can[i + 1][j])
    dfs(i + 1, j);
  if (i - 1 >= 0 && !vis[i - 1][j] && can[i - 1][j])
    dfs(i - 1, j);
  int a = (j + 1) % m;
  int b = (j - 1 + m) % m;
  if (!vis[i][b] && can[i][b])
    dfs(i, b);
  if (!vis[i][a] && can[i][a])
    dfs(i, a);
}
bool solve()
{
  memset(vis, false, sizeof(vis));
  memset(can, false, sizeof(can));
  for (int i = 0; i < n; i++)
  {
    for (int r = 0; r < m; r++)
    {
      int x = r;
      bool ok = 1;
      for (int j = 0; j < m; j++)
      {
        if (s[j] == '1' && t[i][x] == '1')
        {
          ok = 0;
          break;
        }
        x++;
        if (x == m)
          x = 0;
      }
      if (ok)
        can[i][r] = 1;
    }
  }
  for (int i = 0; i < m; i++)
  {
    if (!vis[0][i] && can[0][i])
      dfs(0, i);
  }
  bool ok = 0;
  for (int i = 0; i < m; i++)
    ok |= vis[n - 1][i];
  return ok;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> s;
  for (int i = 0; i < n; i++)
    cin >> t[i];
  bool ok = solve();
  reverse(s.begin(), s.end());
  ok |= solve();
  (ok) ? cout << "Y\n" : cout << "N\n";
}