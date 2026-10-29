
#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int x, y, k;
  cin >> x >> y >> k;
  if (k == 0)
  {
    if (x == y)
      cout << "SIM\n";
    else
      cout << "NAO\n";
  }
  else if (k == 1)
  {
    if ((x + y) != 7 && (x != y))
      cout << "SIM\n";
    else
      cout << "NAO\n";
  }
  else
  {
    cout << "SIM\n";
  }
}