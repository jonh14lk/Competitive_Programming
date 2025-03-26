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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

bitset<MAXN> dp;
int f[MAXN];

int solve(int a, int b, int c)
{
  int g = __gcd(abs(a), abs(b));
  if (c % g)
    return 0;
  return 1;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  int n;
  cin >> n;
  if (n == 1)
  {
    cout << "N\n";
    return 0;
  }
  vector<pi> v(n);
  bool has = 0;
  int g = 0, sum = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    sum += v[i].fir;
    if (v[i].fir == 0)
      has = 1;
    f[v[i].fir]++;
    g = __gcd(g, v[i].sec);
  }
  dp[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    while (f[i] > 2)
    {
      f[i * 2]++;
      f[i] -= 2;
    }
    while (f[i]--)
    {
      dp |= (dp << i);
    }
  }
  for (int i = 0; i <= sum; i++)
  {
    if ((i == 0 || i == sum) && !has)
    {
      continue;
    }
    if (dp[i])
    {
      int c = i - (sum - i);
      if (c % g == 0)
      {
        cout << "Y\n";
        return 0;
      }
    }
  }
  cout << "N\n";
}
// cada blueprint pode produzir uma building de uma altura x que satisfaz:
// x = r * y + g, para y >= 1
// o que eu quero eh separar as blueprints em dois grupos
// tal que eh possivel fazer com que os dois grupos tenham a mesma soma das alturas das buildings

// considerando varias blueprints, tou chutando que posso generalizar como:
// gcd(r[1], r[2], r[3], ..., r[n]) * y + (g[1] + g[2] + g[3] ... + g[n])

// pois se tivermos algo do tipo:
// k = (r[1] * x[1]) + (r[2] * x[2]) + ... + (r[n] * x[n])
// entao esse numero k de certeza eh divisivel pelo gcd(r[1], r[2], r[3], ..., r[n])

// no final para saber se eh possivel vou ter algo do tipo
// ax + b = cy + d
// ax - cy = -b + d
// isso eh uma equação diofantina e eu quero saber se tem solução
// tem solução se (-b + d) % __gcd(a, c) == 0
// dai temos a solucao bruteforce eu acho, brutando por toda separacao possivel e
// checando desse jeito

// note que no check vai ser sempre o mesmo gcd
// entao o problema vai ser so um subset sum no final