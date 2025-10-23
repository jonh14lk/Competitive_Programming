#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    int j = 0;
    while (j < s.size())
    {
      if (s[j] == 'N' && s[j + 1] == 'N')
      {
        ans++;
        j += 2;
      }
      else
      {
        j++;
      }
    }
  }
  cout << ans << endl;
  return 0;
}