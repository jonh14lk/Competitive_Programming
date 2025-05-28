#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define fir first
#define sec second
#define pi pair<int, int>

const int inf = 1e18;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int y, k;
  cin >> y >> k;
  vector<int> divs;
  for (int i = 1; (i * i) <= y; i++)
  {
    if (y % i == 0)
    {
      divs.pb(i);
      if ((y / i) != i)
        divs.pb(y / i);
    }
  }
  sort(divs.begin(), divs.end());
  int x = 1, i = 0;
  while (1)
  {
    pi mn = {inf, inf};
    for (int j = i + 1; j < divs.size(); j++)
    {
      if (divs[j] % divs[i] == 0)
      {
        int div = divs[j] / divs[i];
        mn = {div - 1, j};
        break;
      }
    }
    if (mn.fir > k)
    {
      x += (divs[i] * k);
      break;
    }
    x += (divs[i] * mn.fir);
    k -= mn.fir;
    i = mn.sec;
  }
  cout << x << endl;
}
// uma vez que gcd(x, y) = z
// gcd(x + z, y) >= gcd(x, y) ne