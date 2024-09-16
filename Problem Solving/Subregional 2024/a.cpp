#include <bits/stdc++.h>

using namespace std;

#define int long long int

signed main()
{
  int n, k;
  cin >> n >> k;
  int ans = (k - (n - 1)) / n;
  cout << ans << endl;
  return 0;
}