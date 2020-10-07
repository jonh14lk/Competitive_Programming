#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define mod 998244353
 
lli mult(lli x, lli y)
{
  return (x * 1ll * y) % mod;
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int n;
  cin >> n;
 
  // (81 * (i + 1) + 18) + (i - 1)zeros
  lli dp[n];
  lli dp2[n];
 
  dp[0] = 10;
  dp2[0] = 1;
 
  for (int i = 1; i <= n; i++)
  {
    dp2[i] = mult(dp2[i - 1], 10);
  }
 
  for (int i = 1; i < n; i++)
  {
    dp[i] = mult(81, i + 1);
    dp[i] += 18;
    dp[i] = mult(dp[i], dp2[i - 1]);
  }
 
  for (int i = n - 1; i >= 0; i--)
  {
    cout << dp[i] << " ";
  }
 
  cout << endl;
}
