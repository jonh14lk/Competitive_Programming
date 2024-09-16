#include <bits/stdc++.h>

using namespace std;

#define int long long int

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> cnt(31, 0);
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    for (int b = 0; b <= 30; b++)
    {
      if (x & (1ll << b))
        cnt[b]++;
    }
  }
  vector<int> ans(n, 0);
  for (int b = 0; b <= 30; b++)
  {
    for (int i = 0; i < cnt[b]; i++)
      ans[i] |= (1ll << b);
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << " \n"[i == (n - 1)];
  return 0;
}