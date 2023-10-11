#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 1; i <= n; i++)
  {
    int curr = 0;
    string x;
    cin >> x;
    for (int j = 1; j <= n; j++)
    {
      if (x[j - 1] == 'B')
      {
        ans += curr / 2;
        curr = 0;
      }
      else
      {
        curr++;
      }
    }
    if (curr > 0)
    {
      ans += curr / 2;
    }
  }
  cout << ans << "\n";
  return 0;
}
