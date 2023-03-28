#include <bits/stdc++.h>
using namespace std;

#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int r, c;
int v[101][101];
bool vis[101][101];

int solve(int i, int j)
{
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
      vis[i][j] = 0;
  }
  priority_queue<pii> pq;
  pq.push({-v[i][j], {i, j}});
  vis[i][j] = 1;
  int ans = 0, mx = -1;
  while (!pq.empty())
  {
    int x = pq.top().sec.fir;
    int y = pq.top().sec.sec;
    pq.pop();
    if (v[x][y] <= mx)
      continue;
    mx = v[x][y];
    ans++;
    for (int d = 0; d < 4; d++)
    {
      int ii = x + dx[d], jj = y + dy[d];
      if (ii >= 0 && jj >= 0 && ii < r && jj < c && !vis[ii][jj])
      {
        vis[ii][jj] = 1;
        pq.push({-v[ii][jj], {ii, jj}});
      }
    }
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> r >> c;
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
      cin >> v[i][j];
  }
  int ans = 0;
  for (int i = 0; i < r; i++)
  {
    for (int j = 0; j < c; j++)
      ans = max(ans, solve(i, j));
  }
  cout << ans << endl;
}