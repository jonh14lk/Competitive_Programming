#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300008
#define mod 998244353

const int inf = 1e18;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int l = 1, r = 1000;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    char c;
    cin >> a >> b >> c;
    int mid = (a + b) >> 1;
    int range_a = mid, range_b = mid + 1, eq = -1;
    if (abs(mid - a) == abs(mid - b))
    {
      range_a = mid - 1;
      eq = mid;
    }
    if (c == 'A')
    {
      r = min(r, range_a);
    }
    else if (c == 'B')
    {
      l = max(l, range_b);
    }
    else
    {
      if (eq == -1)
      {
        l = inf;
        break;
      }
      l = max(l, eq);
      r = min(r, eq);
    }
  }
  if (l > r)
  {
    cout << "*\n";
  }
  else
  {
    cout << l << " " << r << endl;
  }
  return 0;
}