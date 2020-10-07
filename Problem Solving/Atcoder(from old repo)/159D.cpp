#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define MAXN 200001
 
lli freq[MAXN];
lli dp[MAXN];
vector<lli> v;
lli sum = 0, aux;
 
int main()
{
  lli n;
  cin >> n;
 
  for (int i = 0; i < n; i++)
  {
    cin >> aux;
    v.pb(aux);
    freq[aux]++;
  }
 
  for (int i = 1; i <= n; i++)
  {
    dp[i] = (freq[i] * (freq[i] - 1)) / 2;
 
    if (dp[i] < 0)
    {
      dp[i] = 0;
    }
 
    sum += dp[i];
  }
 
  for (auto const &i : v)
  {
    lli at = ((freq[i] - 1) * (freq[i] - 2)) / 2;
 
    if (at < 0)
    {
      at = 0;
    }
 
    lli ans = sum;
    ans -= dp[i];
    ans += at;
    cout << ans << endl;
  }
 
  return 0;
}
