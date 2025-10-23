#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, s, l, r;
  cin >> a >> s >> l >> r;
  int ans = (a == s) ? 1 : 0;
  for (int d = 1; d <= (r - l); d++)
  {
    // aqui temos que chutar o termo inicial
    // sabemos a razao, valor d que definimos no for
    // entao a pa eh definida unicamente
    vector<int> le, gt;
    int x = a;
    while (x >= l)
    {
      le.push_back(x);
      x -= d;
    }
    x = a;
    while (x <= r)
    {
      gt.push_back(x);
      x += d;
    }
    reverse(le.begin(), le.end());
    auto sum = [&](int a1, int an)
    {
      int n = (an - a1) / d + 1;
      int ans = ((a1 + an) * n) / 2;
      return ans;
    };
    int j = 0;
    for (auto const &i : le)
    {
      while (j < gt.size() && sum(i, gt[j]) < s)
        j++;
      if (j < gt.size() && sum(i, gt[j]) == s && i != gt[j])
        ans++;
    }
  }
  cout << ans << endl;
  return 0;
}