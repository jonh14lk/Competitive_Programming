#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    int ans = 0;
    while (n >= 10)
    {
      int x = 1;
      while (n)
      {
        x *= (n % 10);
        n /= 10;
      }
      n = x;
      ans++;
    }
    cout << ans << endl;
  }
  return 0;
}