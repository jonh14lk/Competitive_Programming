#include <bits/stdc++.h>
using namespace std;

#define int long long int // avoid overflow
#define mod 1000000007    // modulo

signed main()
{
  string s;
  cin >> s;
  vector<int> dp(13, 0);
  dp[0] = 1;
  for (int i = 0; i < s.size(); i++)
  {
    vector<int> new_dp(13, 0);
    if (s[i] == '?')
    {
      for (int d = 0; d <= 9; d++)
      {
        for (int j = 0; j < 13; j++)
        {
          int new_remainder = ((j * 10) + d) % 13;
          new_dp[new_remainder] = (new_dp[new_remainder] + dp[j]) % mod;
        }
      }
    }
    else
    {
      int d = s[i] - '0';
      for (int j = 0; j < 13; j++)
      {
        int new_remainder = ((j * 10) + d) % 13;
        new_dp[new_remainder] = (new_dp[new_remainder] + dp[j]) % mod;
      }
    }
    swap(dp, new_dp);
  }
  cout << dp[5] << endl;
}