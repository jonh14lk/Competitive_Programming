#include <bits/stdc++.h>
using namespace std;

#define int long long int

int dp[14];

void init()
{
  for (int i = 1; i <= 13; i++)
  {
    dp[i] = 4;
  }
}
int convert(int x)
{
  if (x > 10)
    return 10;
  return x;
}
signed main()
{
  init();
  int n;
  cin >> n;
  int a1 = 0, a2 = 0, sum_j = 0, sum_m = 0;
  cin >> a1 >> a2;
  dp[a1]--;
  dp[a2]--;
  sum_j = convert(a1) + convert(a2);
  cin >> a1 >> a2;
  dp[a1]--;
  dp[a2]--;
  sum_m = convert(a1) + convert(a2);
  for (int i = 1; i <= n; i++)
  {
    int k;
    cin >> k;
    dp[k]--;
    sum_j += convert(k);
    sum_m += convert(k);
  }
  int ans = -1;
  for (int i = 1; i <= 13; i++)
  {
    if (dp[i] > 0)
    {
      if (sum_m + convert(i) == 23 || (sum_j + convert(i) > 23 && sum_m + convert(i) <= 23))
      {
        ans = i;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}