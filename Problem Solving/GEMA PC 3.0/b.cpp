#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

int n, x, k;
int h[MAXN];
int f[MAXN];

bool possible(int m)
{
  int ans = 0;
  for (int i = 0; i < n; i++)
    if (h[i] >= m)
      ans += f[i];
  return ans >= x;
}
bool ok(int m)
{
  int ans = 0;
  for (int i = 0; i < n; i++)
    if (h[i] >= k && f[i] >= m)
      ans += f[i];
  return ans >= x;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    cin >> n >> x;
    for (int i = 0; i < n; i++)
      cin >> h[i];
    for (int i = 0; i < n; i++)
      cin >> f[i];
    int i = 0, f = INT_MAX, m;
    while (i < f)
    {
      m = (i + f) >> 1;
      if (possible(m))
        i = m + 1;
      else
        f = m;
    }
    if (i == 0)
    {
      cout << "Impossible\n";
      continue;
    }
    k = i - 1, i = 0, f = INT_MAX, m;
    while (i < f)
    {
      m = (i + f) >> 1;
      if (ok(m))
        i = m + 1;
      else
        f = m;
    }
    if (i == 0)
    {
      cout << "Impossible\n";
      continue;
    }
    cout << k << " " << i - 1 << endl;
  }
}