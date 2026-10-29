
#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int n, k;
  cin >> n >> k;
  if (k > (n / 2))
  {
    cout << "impossivel\n";
  }
  else
  {
    for (int i = 0; i < n; i++)
    {
      if (i < k)
        cout << "b";
      else
        cout << "a";
    }
    cout << endl;
  }
}