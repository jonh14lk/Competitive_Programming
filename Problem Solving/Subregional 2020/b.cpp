#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007

int v[10][10];

bool is_inside(int i, int j)
{
  return (i < 10 && i >= 0 && j < 10 && j >= 0);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  bool ans = true;
  for (int i = 0; i < n; i++)
  {
    int d, l, r, c;
    cin >> d >> l >> r >> c;
    r--, c--;
    if (!d)
    {
      for (int j = c; j <= c + l - 1; j++)
      {
        if (!is_inside(r, j))
          ans = false;
        else if (v[r][j])
          ans = false;
        else
          v[r][j] = true;
      }
    }
    else
    {
      for (int j = r; j <= r + l - 1; j++)
      {
        if (!is_inside(j, c))
          ans = false;
        else if (v[j][c])
          ans = false;
        else
          v[j][c] = true;
      }
    }
  }
  (ans) ? cout << "Y\n" : cout << "N\n";
  return 0;
}