#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct dsu
{
  vector<int> parent;
  vector<int> sz;
  vector<int> sum;
  vector<pi> range;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    sum.assign(n, 0);
    range.assign(n, {-1, -1});
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
  void make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      sum[y] += sum[x];
      if (range[y].fir == -1 && range[x].fir != -1)
        range[y] = range[x];
    }
  }
  void set_time(int x, int a, int t)
  {
    x = find_set(x);
    range[x] = {a, a + t};
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int f, n;
  cin >> f >> n;
  vector<int> p(n);
  vector<int> k(n);
  map<int, int> pos;
  for (int i = 0; i < n; i++)
  {
    cin >> k[i] >> p[i];
    pos[k[i]] = i;
  }
  dsu d(n);
  for (int i = 0; i < n; i++)
  {
    d.sum[i] = p[i];
  }
  for (int i = 0; i < n; i++)
  {
    char c;
    cin >> c;
    if (c == 'A')
    {
      int a, t;
      cin >> a >> t;
      d.set_time(i, a, t);
    }
    else if (c == 'T')
    {
      int nxt;
      cin >> nxt;
      if (pos.find(nxt) != pos.end())
      {
        nxt = pos[nxt];
        d.make_set(i, nxt);
      }
    }
  }
  map<int, int> delta;
  for (int i = 0; i < n; i++)
  {
    if (d.find_set(i) == i && d.range[i].fir != -1)
    {
      delta[d.range[i].fir] += d.sum[i];
      delta[d.range[i].sec] -= d.sum[i];
    }
  }
  int curr = 0, ans = 0;
  for (auto const &i : delta)
  {
    curr += i.sec;
    ans = max(ans, curr);
  }
  cout << ans << endl;
  return 0;
}