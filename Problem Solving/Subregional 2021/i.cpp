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
#define MAXN 105
#define mod 1000000007

int n, m;
int adj[MAXN][MAXN];

struct dsu
{
  vector<int> parent;
  vector<int> sz;
  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  bool make_set(int x, int y)
  {
    x = find_set(x);
    y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      return true;
    }
    return false;
  }
};
void invert(int i)
{
  for (int j = 0; j < n; j++)
  {
    if (i != j)
    {
      adj[i][j] ^= 1;
      adj[j][i] ^= 1;
    }
  }
}
bool check()
{
  dsu d(n);
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (adj[i][j])
      {
        if (!d.make_set(i, j))
          return false;
      }
    }
  }
  return (d.sz[d.find_set(0)] == n);
}
bool has_cycle(int lim)
{
  dsu d(lim);
  for (int i = 0; i < lim; i++)
  {
    for (int j = i + 1; j < lim; j++)
    {
      if (adj[i][j])
      {
        if (!d.make_set(i, j))
          return true;
      }
    }
  }
  return false;
}
int solve(int i)
{
  if (i == n)
    return check();
  if (has_cycle(i))
    return 0;
  int ret = 0;
  invert(i);
  ret += solve(i + 1);
  invert(i);
  ret += solve(i + 1);
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a][b] = 1;
    adj[b][a] = 1;
  }
  cout << solve(0) << endl;
  return 0;
}