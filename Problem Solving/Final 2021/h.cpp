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
#define MAXN 505
#define mod 998244353

struct hungarian
{
  int n, inf;
  vector<vector<int>> a;
  vector<int> u, v, p, way;

  hungarian(int n_) : n(n_), u(n + 1), v(n + 1), p(n + 1), way(n + 1)
  {
    a = vector<vector<int>>(n, vector<int>(n));
    inf = numeric_limits<int>::max();
  }
  void add_edge(int x, int y, int c)
  {
    a[x][y] = c;
  }
  pair<int, vector<int>> run()
  {
    for (int i = 1; i <= n; i++)
    {
      p[0] = i;
      int j0 = 0;
      vector<int> minv(n + 1, inf);
      vector<int> used(n + 1, 0);
      do
      {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        int delta = inf;
        for (int j = 1; j <= n; j++)
        {
          if (!used[j])
          {
            int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
            if (cur < minv[j])
              minv[j] = cur, way[j] = j0;
            if (minv[j] < delta)
              delta = minv[j], j1 = j;
          }
        }
        for (int j = 0; j <= n; j++)
        {
          if (used[j])
            u[p[j]] += delta, v[j] -= delta;
          else
            minv[j] -= delta;
        }
        j0 = j1;
      } while (p[j0] != 0);
      do
      {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    vector<int> ans(n);
    for (int j = 1; j <= n; j++)
      ans[p[j] - 1] = j - 1;
    return make_pair(-v[0], ans);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<vector<int>> c(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
      cin >> c[i][j];
  }
  int sz = (n + 1) >> 1;
  hungarian h(sz);
  for (int i = 1; i <= n; i += 2)
  {
    for (int j = 2; j <= n; j += 2)
    {
      int cc = c[i][j];
      if (j - 2 >= 0)
        cc += c[j - 2][i];
      h.add_edge(i / 2, (j - 1) / 2, cc);
    }
    if (n & 1)
      h.add_edge(i / 2, sz - 1, c[n - 1][i]);
  }
  cout << h.run().fir << endl;
  return 0;
}