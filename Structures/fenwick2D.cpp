
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1025
#define mod 1000000007

int b[MAXN][MAXN];
int vv[MAXN][MAXN];

int qry(int x, int y)
{
  int sum = 0;
  for (; x >= 0; x = (x & (x + 1)) - 1)
  {
    for (int yy = y; yy >= 0; yy = (yy & (yy + 1)) - 1)
      sum += b[x][yy];
  }
  return sum;
}
void add(int x, int y, int v)
{
  for (; x < MAXN; x = x | (x + 1))
  {
    for (int yy = y; yy < MAXN; yy = yy | (yy + 1))
      b[x][yy] += v;
  }
}
int qry2(int x1, int y1, int x2, int y2)
{
  return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
}
void add2(int x1, int y1, int x2, int y2, int v)
{
  add(x1, y1, v);
  add(x1, y2 + 1, -v);
  add(x2 + 1, y1, -v);
  add(x2 + 1, y2 + 1, v);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) // reseta
    {
      for (int j = 0; j < n; j++)
      {
        add(i, j, -vv[i][j]);
        vv[i][j] = 0;
      }
    }
    while (1)
    {
      string s;
      cin >> s;
      if (s == "SET")
      {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, -vv[a][b]);
        vv[a][b] = c;
        add(a, b, vv[a][b]);
      }
      else if (s == "SUM")
      {
        int a, b, c, d;
        cin >> a >> b >> c >> d; // c >= a e d >= b
        cout << qry2(a, b, c, d) << endl;
      }
      else
      {
        break;
      }
    }
  }
  return 0;
}
// to test: https://www.spoj.com/problems/MATSUM/
