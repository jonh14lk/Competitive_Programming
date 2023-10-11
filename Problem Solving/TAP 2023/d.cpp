#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k;
  cin >> k;
  vector<int> c(k);
  for (int i = 0; i < k; i++)
    cin >> c[i];
  vector<int> p(k);
  for (int i = 0; i < k; i++)
    cin >> p[i];
  auto can = [&](int mid)
  {
    vector<int> stk;
    for (int i = k - 1; i >= 0; i--)
    {
      stk.pb(c[i] * mid);
      int x = p[i];
      while (stk.size() > 0 && x > 0)
      {
        int to_sub = min(x, stk.back());
        x -= to_sub;
        stk.back() -= to_sub;
        if (stk.back() == 0)
          stk.pop_back();
      }
    }
    return (stk.size() == 0);
  };
  int l = 0, r = 1000000005;
  while (l < r)
  {
    int mid = (l + r + 1) >> 1;
    (can(mid)) ? l = mid : r = mid - 1;
  }
  cout << l << endl;
  return 0;
}
// um contest precisa do seguinte:
// ter c[i] problemas com o nivel i

// existem p[i] questoes com o nivel i
// se uma questão tem o nivel i, então

// se um problema tem um nivel sendo i
// ele pode ser usado no contest com um nivel j
// se j >= i