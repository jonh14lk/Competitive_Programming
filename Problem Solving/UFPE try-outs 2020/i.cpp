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
#define fir first
#define sec second
#define MAXN 1000005
#define mod 1000000007

int s, n, m;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
bool vis[MAXN];
vector<vector<int>> v;
vector<pii> pq;

bool is_inside(int i, int j)
{
  return (i >= 0 && i < n && j >= 0 && j < m);
}
int idx(int i, int j)
{
  return (i * m) + j;
}
namespace dsu
{
  int parent[MAXN];
  int minn[MAXN];
  int sz[MAXN];

  int Find(int i)
  {
    return parent[i] = (parent[i] == i) ? i : Find(parent[i]);
  }
  void Union(int x, int y)
  {
    int xx = Find(x), yy = Find(y);
    if (xx != yy)
    {
      minn[yy] = min(minn[yy], minn[xx]);
      sz[yy] += sz[xx];
      parent[xx] = yy;
    }
  }
  void init()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        int k = idx(i, j);
        sz[k] = 1;
        minn[k] = v[i][j];
        parent[k] = k;
      }
    }
  }
} // namespace dsu
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s >> n >> m;
  v.resize(n);
  for (int i = 0; i < n; i++)
  {
    v[i].resize(m);
    for (int j = 0; j < m; j++)
    {
      cin >> v[i][j];
      pq.pb({v[i][j], {i, j}});
    }
  }
  sort(pq.rbegin(), pq.rend());
  dsu::init();
  for (int j = 0; j < pq.size(); j++)
  {
    pi u = pq[j].sec;
    vis[idx(u.fir, u.sec)] = true;
    for (int i = 0; i < 4; i++)
    {
      pi k = {u.fir + dx[i], u.sec + dy[i]};
      if (is_inside(k.fir, k.sec) && vis[idx(k.fir, k.sec)])
        dsu::Union(idx(u.fir, u.sec), idx(k.fir, k.sec));
    }
    int uu = dsu::Find(idx(u.fir, u.sec));
    if (dsu::sz[uu] >= s)
    {
      cout << dsu::minn[uu] << endl;
      return 0;
    }
  }
  return 0;
}