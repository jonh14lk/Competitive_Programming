#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200001
#define mod 998244353

namespace dio
{
  vector<pi> sols;

  int gcd(int a, int b, int &x, int &y)
  {
    if (b == 0)
    {
      x = 1, y = 0;
      return a;
    }
    int x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1, y = x1 - y1 * (a / b);
    return d;
  }
  void one_sol(int a, int b, int c)
  {
    int x0, y0, g;
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g)
      return;
    x0 *= (c / g);
    y0 *= (c / g);
    if (a < 0)
      x0 *= -1;
    if (b < 0)
      y0 *= -1;
    sols.pb({x0, y0});
  }
  void more_sols(int a, int b, int c)
  {
    int g = __gcd(a, b);
    int x0 = sols[0].fir, y0 = sols[0].sec;
    for (int k = -200000; k <= 200000; k++)
    {
      int x = x0 + k * (b / g);
      int y = y0 - k * (a / g);
      sols.pb({x, y});
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, b, c;
  cin >> a >> b >> c;
  dio::one_sol(a, b, c);
  if (!dio::sols.size())
  {
    cout << "No\n";
    return 0;
  }
  dio::more_sols(a, b, c);
  bool can = false;
  for (auto const &i : dio::sols)
    can |= (i.fir >= 0 && i.sec >= 0);
  (can) ? cout << "Yes\n" : cout << "No\n";
  return 0;
}
// equacoes do tipo:
// ax + by = c
// o caso a = 0 e b = 0, nao eh tratado nesse codigo
// nesse caso quero checar se equacao diofantina tem uma solucao
// com x >= 0 e y >= 0
