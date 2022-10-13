#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1010
#define mod 1000000007

bool adj[MAXN][MAXN][4];
pi parent[MAXN][MAXN];
int sz[MAXN][MAXN];
bool vis[MAXN][MAXN];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int bfs(int x, int y)
{
  queue<pi> q;
  q.push({x, y});
  vis[x][y] = 1;
  int cnt = 1;
  while (!q.empty())
  {
    int i = q.front().fir;
    int j = q.front().sec;
    q.pop();
    for (int d = 0; d < 4; d++)
    {
      if (adj[i][j][d])
      {
        int x = i + dx[d];
        int y = j + dy[d];
        if (!vis[x][y])
        {
          vis[x][y] = 1;
          cnt++;
          q.push({x, y});
        }
      }
    }
  }
  return cnt;
}
pi find_set(pi i)
{
  return parent[i.fir][i.sec] = (parent[i.fir][i.sec] == i) ? i : find_set(parent[i.fir][i.sec]);
}
void make_set(pi x, pi y)
{
  x = find_set(x), y = find_set(y);
  if (x != y)
  {
    if (sz[x.fir][x.sec] > sz[y.fir][y.sec])
      swap(x, y);
    parent[x.fir][x.sec] = y;
    sz[y.fir][y.sec] += sz[x.fir][x.sec];
  }
}
void init()
{
  for (int i = 0; i < MAXN; i++)
  {
    for (int j = 0; j < MAXN; j++)
    {
      parent[i][j] = {i, j};
      sz[i][j] = 1;
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  n++;
  init();
  vector<pi> v;
  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    x += 2, y += 2;
    v.pb({x, y});
  }
  for (int i = 1; i < n; i++)
  {
    if (v[i].fir == v[i - 1].fir)
    {
      int l = min(v[i].sec, v[i - 1].sec);
      int r = max(v[i].sec, v[i - 1].sec);
      for (int j = l; j < r; j++)
        make_set({v[i].fir, j + 1}, {v[i].fir - 1, j + 1});
    }
    else
    {
      int l = min(v[i].fir, v[i - 1].fir);
      int r = max(v[i].fir, v[i - 1].fir);
      for (int j = l; j < r; j++)
        make_set({j, v[i].sec}, {j, v[i].sec + 1});
    }
  }
  for (int i = 0; i < MAXN; i++)
  {
    for (int j = 0; j < MAXN; j++)
    {
      for (int d = 0; d < 4; d++)
      {
        int x = i + dx[d];
        int y = j + dy[d];
        if (x < 0 || y < 0 || y >= MAXN || x >= MAXN)
          continue;
        if (find_set({i, j}) != find_set({x, y}))
          adj[i][j][d] = 1;
      }
    }
  }
  bfs(0, 0);
  int ans = 0;
  for (int i = 0; i < MAXN; i++)
  {
    for (int j = 0; j < MAXN; j++)
    {
      if (!vis[i][j])
        ans = max(ans, bfs(i, j));
    }
  }
  cout << ans << endl;
  return 0;
}