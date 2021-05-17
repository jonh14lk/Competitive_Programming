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
#define MAXN 200001
#define mod 1000000007

struct point
{
  int x, y, cof;
  long double ang;
};

int kadane(vector<int> v)
{
  int n = v.size(), ans = 0, max_here = 0;
  for (int i = 0; i < n; i++)
  {
    max_here += v[i];
    if (ans < max_here)
      ans = max_here;
    if (max_here < 0)
      max_here = 0;
  }
  return ans;
}
int kadane_circular(vector<int> v)
{
  int n = v.size(), max_kadane = kadane(v);
  int max_wrap = 0, i;
  for (i = 0; i < n; i++)
  {
    max_wrap += v[i];
    v[i] = -v[i];
  }
  max_wrap += kadane(v);
  return max(max_wrap, max_kadane);
}
bool cmp(point a, point b)
{
  return a.ang < b.ang;
}
signed main()
{
  int n;
  cin >> n;
  vector<point> v(n);
  for (int i = 0; i < n; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    v[i].x = a, v[i].y = b;
    v[i].cof = c - d;
    v[i].ang = atan2l(v[i].y, v[i].x);
  }
  sort(v.begin(), v.end(), cmp);
  vector<int> lines;
  int l = 0;
  while (l < n)
  {
    int r = l, curr = 0;
    while (r < n && v[l].ang == v[r].ang)
    {
      curr += v[r].cof;
      r++;
    }
    lines.pb(curr);
    l = r;
  }
  cout << kadane_circular(lines) << endl;
  return 0;
}