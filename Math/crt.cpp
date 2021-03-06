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
#define MAXN 10001
#define mod 998244353

int n;
vector<int> x;
vector<int> p;

namespace crt
{
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
  int inv(int a, int m)
  {
    int x, y;
    gcd(a, m, x, y);
    x = (x % m + m) % m;
    return x;
  }
  bool check()
  {
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        if (__gcd(p[i], p[j]) != 1)
          return false;
    return true;
  }
  int crt()
  {
    int prod = 1, ans = 0;
    for (int i = 0; i < n; i++)
      prod *= p[i];
    for (int i = 0; i < n; i++)
    {
      int pp = prod / p[i];
      ans += x[i] * inv(pp, p[i]) * pp;
    }
    return ans % prod;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  x.resize(n);
  p.resize(n);
  for (int i = 0; i < n; i++)
    cin >> x[i] >> p[i];
  (!crt::check()) ? cout << -1 << endl : cout << crt::crt() << endl;
  return 0;
}
// teorema chines do resto(crt)
// para resolver sistemas de congruencias modulares
// o menor inteiro a que satisfaz:
// a mod p1 = x1
// a mod p2 = x2
// ...
// a mod pn = xn
// 1 - existe solução caso não exista um par p[i] p[j] com i != j e gcd(p[i], p[j]) > 1
// a = ∑ (x[i] * pp[i] * inv[i]) % prod
// x[i] -> resposta de cada congruencia
// prod -> produto de todos os p[i]
// pp[i] -> prod / p[i]
// inv[i] -> inverso modular de pp[i] em relação a p[i]
// note que, para achar o inverso, como o mod nao eh primo
// o metodo que usa exponenciação binaria nao funciona
// nesse caso, para achar o inverso, podemos pensar em uma equação diofantina
// ax + my = 1
// pondo mod m
// ax mod m = 1 mod m
// no final a complexidade fica
// O(n^2) para checar se a resposta existe (tem como fazer isso melhor)
// O(n * log(n)) para achar a resposta
