#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back

signed main()
{
  int n;
  cin >> n;
  vector<int> dp(2, 0);
  dp[0] = 1;
  int ans = 0;
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    sum = (sum + x) % 2;
    int ot = sum ^ 1;
    ans += dp[ot];
    dp[sum]++;
  }
  cout << ans << endl;
}