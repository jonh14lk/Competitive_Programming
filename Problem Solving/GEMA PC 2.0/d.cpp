#include <bits/stdc++.h>
using namespace std;

#define DEBUG(X) if (X)
#define pb push_back

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<vector<ii>> vvii;
typedef long long int lli;
vector<string> mapa;

int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
vector<vector<bool>> visited;
bool out(int n, int m, int x, int y)
{
  return (x < 0 || y < 0 || x == n || y == m || visited[x][y]);
}
int go(int x, int y, int n, int m, char value)
{
  if (out(n, m, x, y) || value != mapa[x][y])
  {
    return 0;
  }
  visited[x][y] = true;
  int qnt = 1;
  for (int i = 0; i < 8; i++)
  {
    int nx = x + dx[i];
    int ny = y + dy[i];
    qnt += go(nx, ny, n, m, value);
  }
  return qnt;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  cin.ignore();
  mapa.resize(n);
  visited.resize(n);
  for (int i = 0; i < n; i++)
  {
    cin >> mapa[i];
    visited[i].resize(m);
  }
  int best = 0, qnt = 0;
  bool flag = true;
  while (flag)
  {
    flag = false;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (!visited[i][j])
        {
          flag = true;
          qnt++;
          best = max(best, go(i, j, n, m, mapa[i][j]));
        }
      }
    }
  }
  cout << qnt << " " << best << endl;
  return 0;
}