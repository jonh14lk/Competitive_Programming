#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 11
#define mod 1000000007
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int n, m, c;
string s;
bool ans;
map<char, vector<pi>> mm;

bool is_inside(pi i)
{
  return (i.fir >= 0 && i.fir < n && i.sec >= 0 && i.sec < m);
}
bool check(vector<vector<char>> grid)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (grid[i][j] == '.')
        return false;
  return true;
}
void dfs(pi i, pi j, int cnt, vector<vector<char>> grid) // just brute all and verify the answer
{
  if (i == j)
  {
    if (cnt == s.size() - 1 && check(grid))
    {
      ans = true;
    }
    else if (cnt != s.size() - 1)
    {
      cnt++;
      char curr = s[cnt];
      grid[mm[curr][1].fir][mm[curr][1].sec] = '.';
      dfs(mm[curr][0], mm[curr][1], cnt, grid);
    }
    return;
  }
  for (int ff = 0; ff < 4; ff++)
  {
    if (is_inside({i.fir + dx[ff], i.sec + dy[ff]}) && grid[i.fir + dx[ff]][i.sec + dy[ff]] == '.')
    {
      grid[i.fir + dx[ff]][i.sec + dy[ff]] = grid[i.fir][i.sec];
      dfs({i.fir + dx[ff], i.sec + dy[ff]}, j, cnt, grid);
      grid[i.fir + dx[ff]][i.sec + dy[ff]] = '.';
    }
  }
}
signed main()
{
  int q;
  cin >> q;
  while (q--)
  {
    mm.clear();
    cin >> n >> m >> c >> s;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        cin >> grid[i][j];
        if (grid[i][j] != '.')
          mm[grid[i][j]].pb({i, j});
      }
    }
    ans = false;
    char curr = s[0];
    grid[mm[curr][1].fir][mm[curr][1].sec] = '.';
    dfs(mm[curr][0], mm[curr][1], 0, grid);
    (ans) ? cout << "Yes\n" : cout << "No\n";
  }
  return 0;
}