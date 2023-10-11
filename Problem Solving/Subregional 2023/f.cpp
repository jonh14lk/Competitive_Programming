#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back

signed main()
{
  int d, r, c;
  cin >> d >> c >> r;
  vector<int> v(c);
  for (int i = 0; i < c; i++)
    cin >> v[i];
  vector<int> v2(r);
  for (int i = 0; i < r; i++)
    cin >> v2[i];
  int a = 0, b = 0, ans = 0;
  while (a < c)
  {
    if (d >= v[a])
    {
      ans++;
      d -= v[a];
      a++;
    }
    else if (b < r)
    {
      ans++;
      d += v2[b];
      b++;
    }
    else
    {
      break;
    }
  }
  ans += (r - b);
  cout << ans << endl;
}