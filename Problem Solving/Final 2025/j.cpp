#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  string s;
  cin >> s;
  int ans = 0, n = s.size();
  for (int j = 0; j < n; j++)
  {
    if ((j - 1) >= 0 && s.substr(j - 1, 2) == "ha")
      ans++;
    if ((j - 4) >= 0 && s.substr(j - 4, 5) == "boooo")
      ans--;
    if ((j - 4) >= 0 && s.substr(j - 4, 5) == "bravo")
      ans += 3;
  }
  cout << ans << endl;
}