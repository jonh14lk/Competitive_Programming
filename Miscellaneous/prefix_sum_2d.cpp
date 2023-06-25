// https://cses.fi/problemset/task/1652
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

int v[1001][1001];
int p[1001][1001];

int qry(int x1, int y1, int x2, int y2)
{
  return p[x2 + 1][y2 + 1] - p[x2 + 1][y1] - p[x1][y2 + 1] + p[x1][y1];
}
signed main()
{
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      char c;
      cin >> c;
      v[i][j] = (c == '*');
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      p[i + 1][j + 1] = p[i][j + 1] + p[i + 1][j] - p[i][j];
      p[i + 1][j + 1] += v[i][j];
    }
  }
  while (q--)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    cout << qry(a, b, c, d) << endl;
  }
  return 0;
}
// prefix sum 2d
// me enrolo pra codar toda vez, é bom deixar na lib