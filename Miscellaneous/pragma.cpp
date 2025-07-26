#include <iostream>
using namespace std;
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

int b[100005];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i)
  {
    cin >> b[i];
  }
  for (int j = 0; j < k; ++j)
  {
    char c;
    int l, r;
    cin >> c >> l >> r;
    l--, r--;
    if (c == 'Q')
    {
      int mx = -1;
      for (int i = l; i <= r; ++i)
        mx = max(mx, b[i]);
      cout << mx << endl;
    }
    else if (c == 'A')
    {
      for (int i = l; i <= r; ++i)
        ++b[i];
    }
    else
    {
      int mx = -1;
      for (int i = 0; i < n; ++i)
        mx = max(mx, b[i]);
      if (mx == 0)
        continue;
      for (int i = l; i <= r; ++i)
      {
        if (b[i] == mx)
          b[i] = 0;
      }
    }
  }
  return 0;
}
// problema que da para roubar fazendo o naive com pragma: https://codeforces.com/gym/105873/problem/F
// https://codeforces.com/blog/entry/66279