#include <bits/stdc++.h>
using namespace std;

#define int long long int // avoid overflow

int sum_ap(int x)
{
  return ((1 + x) * x) / 2;
}
signed main()
{
  int n;
  cin >> n;
  int walked = 1, last_jump = 1, ans = 1;
  while (walked < n)
  {
    ans++;
    int remaining = n - walked;
    if (sum_ap(last_jump + 1) <= remaining)
    {
      walked += last_jump + 1;
      last_jump++;
    }
    else if (sum_ap(last_jump) <= remaining)
    {
      walked += last_jump;
    }
    else
    {
      walked += last_jump - 1;
      last_jump--;
    }
  }
  cout << ans << endl;
}