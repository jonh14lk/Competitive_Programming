
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define mod 1000000007

signed main()
{
  int n;
  cin >> n;
  int ans = 1;
  for (int i = 0; i <= 49; i++)
    ans = (ans * (n - i)) % mod;
  cout << ans << endl;
}