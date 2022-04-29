#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define x first
#define y second
#define MAXN 1005
#define mod 998244353

struct poly
{
  char c;
  int dx, dy, sz;
  pi v[101];
  void read()
  {
    cin >> c >> sz;
    for (int i = 0; i < sz; i++)
    {
      cin >> v[i].x >> v[i].y;
      v[i].x *= 3;
      v[i].y *= 3;
    }
    get_dir();
  }
  void get_dir()
  {
    dx = 0, dy = 0;
    if (c == 'N')
      dy++;
    else if (c == 'S')
      dy--;
    else if (c == 'E')
      dx++;
    else
      dx--;
  }
  vector<pi> translate(int x)
  {
    vector<pi> ans;
    for (auto const &i : v)
      ans.pb({i.x + (x * dx), i.y + (x * dy)});
    return ans;
  }
};

int n;
poly v[101];
bool vis[301][301][310];
bool dp[301][301][310];
bool can[301][301][310];
bool can0[301][301][101];
int mat[301][301];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is(int x, int y)
{
  return (x >= 0 && x <= 300 && y >= 0 && y <= 300);
}
void dfs(int x, int y)
{
  mat[x][y] = 2;
  for (int d = 0; d < 4; d++)
  {
    int i = x + dx[d], j = y + dy[d];
    if (!is(i, j) || mat[i][j] != 0)
      continue;
    dfs(i, j);
  }
}
bool get(int i, int j, int k)
{
  if (dp[i][j][k])
    return can[i][j][k];
  dp[i][j][k] = 1;
  can[i][j][k] = 1;
  for (int id = 0; id < n; id++)
  {
    int x = i - (k * v[id].dx), y = j - (k * v[id].dy);
    if (is(x, y) && !can0[x][y][id])
      return can[i][j][k] = 0;
  }
  return 1;
}
signed main()
{
  int a, b, c, d;
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> a >> b >> c >> d >> n;
  a *= 3, b *= 3, c *= 3, d *= 3;
  for (int i = 0; i < n; i++)
    v[i].read();
  for (int k = 0; k < n; k++)
  {
    memset(mat, 0, sizeof(mat));
    pi to_fill = {-1, -1};
    for (int i = 0; i < v[k].sz; i++)
    {
      int j = (i + 1) % v[k].sz;
      if (v[k].v[i].x == v[k].v[j].x)
      {
        int a = min(v[k].v[i].y, v[k].v[j].y);
        int b = max(v[k].v[i].y, v[k].v[j].y);
        for (int _ = a; _ <= b; _++)
          mat[v[k].v[i].x][_] = 1;
        pi curr = {v[k].v[i].x - 1, (a + b) >> 1};
        to_fill = max(to_fill, curr);
      }
      else
      {
        int a = min(v[k].v[i].x, v[k].v[j].x);
        int b = max(v[k].v[i].x, v[k].v[j].x);
        for (int _ = a; _ <= b; _++)
          mat[_][v[k].v[i].y] = 1;
      }
    }
    dfs(to_fill.x, to_fill.y);
    for (int i = 0; i <= 300; i++)
    {
      for (int j = 0; j <= 300; j++)
        can0[i][j][k] = (mat[i][j] == 2) ? 0 : 1;
    }
  }
  queue<pii> q;
  q.push({0, {a, b}});
  while (!q.empty())
  {
    int x = q.front().y.x;
    int y = q.front().y.y;
    int t = q.front().x;
    q.pop();
    if (vis[x][y][t])
      continue;
    vis[x][y][t] = 1;
    if (t + 3 <= 309)
    {
      for (int d = 0; d < 4; d++)
      {
        int i = x + dx[d], j = y + dy[d];
        int i2 = x + (2 * dx[d]), j2 = y + (2 * dy[d]);
        int i3 = x + (3 * dx[d]), j3 = y + (3 * dy[d]);
        if (!is(i3, j3))
          continue;
        if (get(i, j, t + 1) && get(i2, j2, t + 2) && get(i3, j3, t + 3))
          q.push({t + 3, {i3, j3}});
      }
      q.push({t + 3, {x, y}}); // parado
    }
  }
  int ans = 1e9;
  for (int i = 0; i <= 309; i++)
  {
    if (vis[c][d][i])
    {
      ans = i / 3;
      break;
    }
  }
  for (int i = 0; i <= 300; i++)
  {
    for (int j = 0; j <= 300; j++)
    {
      if (vis[i][j][309])
      {
        int t = (abs(i - c) / 3) + (abs(j - d) / 3) + 103;
        ans = min(ans, t);
      }
    }
  }
  cout << ans << endl;
  return 0;
}