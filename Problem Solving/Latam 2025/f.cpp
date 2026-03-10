#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200006
#define mod 998244353

int n;
int col[350];
int mat[350][350];
bool vis[350][350];
int v[155];
int dx[] = {0, 1, 1, 0, -1, -1};
int dy[] = {1, 0, -1, -1, 0, 1};

int dfs(int i, int j)
{
  int ans = 1;
  vis[i][j] = 1;
  for (int dir = 0; dir < 6; dir++)
  {
    int x = i + dx[dir];
    int y = j + dy[dir];
    if (y >= 0 && y < col[x] && !vis[x][y] && mat[i][j] == mat[x][y])
      ans += dfs(x, y);
  }
  return ans;
}
int solve(int i, int l, int r)
{
  if (i >= n)
  {
    for (int i = l + 1; i < r; i++)
    {
      for (int j = 0; j < col[i]; j++)
        vis[i][j] = 0;
    }
    int ans = 0;
    for (int i = l + 1; i < r; i++)
    {
      for (int j = 0; j < col[i]; j++)
      {
        if (!vis[i][j])
        {
          int curr = dfs(i, j);
          ans = max(ans, curr);
        }
      }
    }
    return ans;
  }
  int ans = -1e18;
  vector<int> backup(350);
  int prv_i = i;
  for (int j = 0; j < 350; j++)
  {
    backup[j] = col[j];
  }
  { // put on right
    for (int j = r; j > l; j--)
    {
      if (i < n)
      {
        mat[j][col[j]] = v[i];
        col[j]++;
        i++;
      }
      else
      {
        break;
      }
    }
    ans = max(ans, solve(i, l, r + 1));
    i = prv_i;
    for (int j = 0; j < 350; j++)
      col[j] = backup[j];
  }
  { // put on left
    for (int j = l; j < r; j++)
    {
      if (i < n)
      {
        mat[l][col[l]] = v[i];
        col[l]++;
        i++;
      }
      else
      {
        break;
      }
    }
    ans = max(ans, solve(i, l - 1, r));
    i = prv_i;
    for (int j = 0; j < 350; j++)
      col[j] = backup[j];
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  mat[155][col[155]] = v[0];
  col[155]++;
  cout << solve(1, 154, 156) << endl;
  return 0;
}