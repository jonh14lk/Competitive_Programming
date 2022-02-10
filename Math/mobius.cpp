#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 5000005
#define mod 1000000001

int lpf[MAXN];
int mobius[MAXN];
int g[MAXN];

void calc_lpf()
{
  for (int i = 2; i < MAXN; i++)
  {
    if (!lpf[i])
    {
      for (int j = i; j < MAXN; j += i)
      {
        if (!lpf[j])
          lpf[j] = i;
      }
    }
  }
}
void calc_mobius()
{
  calc_lpf();
  mobius[1] = 1;
  for (int i = 2; i < MAXN; i++)
  {
    if (lpf[i / lpf[i]] == lpf[i])
      mobius[i] = 0;
    else
      mobius[i] = -1 * mobius[i / lpf[i]];
  }
}
int count_pairs(int n)
{
  // f(n) -> contar pares (i, j) com __gcd(i, j) == 1 e 1 <= i, j <= n
  int ans = 0;
  for (int d = 1; d <= n; d++)
  {
    // quadrado pq sao pares (2 caras)
    // mas se fossem x caras seria (n / d)^x
    int sq = (n / d) * (n / d);
    int x = mobius[d] * sq;
    ans += x;
  }
  return ans;
}
int gcd_sum(int n)
{
  // soma de todos os gcd(i, j) com 1 <= i, j <= n
  int ans = 0;
  for (int k = 1; k <= n; k++) // fixa o valor do gcd(i, j) e conta quantos pares com gcd(i, j) == k
  {
    int lim = n / k;
    int curr = k * count_pairs(lim);
    ans += curr;
  }
  return ans;
}
int lcm_sum(int n)
{
  // soma de todos os lcm(i, j) com 1 <= i, j <= n
  for (int i = 1; i <= n; i++)
    g[i] = 0;
  for (int i = 1; i <= n; i++)
  {
    for (int j = i; j <= n; j += i)
      g[j] += (mobius[i] * j * i);
  }
  int ans = 0;
  for (int l = 1; l <= n; l++)
  {
    int cima = (1 + n / l) * (n / l);
    int f = (cima / 2) * (cima / 2);
    f *= g[l];
    ans += f;
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  calc_mobius();
  for (int i = 1; i <= q; i++)
  {
    int n;
    cin >> n;
    int ans = lcm_sum(n);
    for (int i = 1; i <= n; i++)
      ans -= i;
    ans /= 2;
    cout << "Case " << i << ": " << ans << endl;
  }
  return 0;
}
// https://codeforces.com/blog/entry/53925
// mobius inversion
// sejam f(x) e g(x) funções
// e g(x) é definida da seguinte maneira
// g(x) = soma dos f(d), no qual d eh um divisor de x

// temos que:
// f(n) = soma dos (g(d) * u(n / d)), no qual d eh um divisor de x
// u(x) -> mobius function

// propiedade legal:
// seja l(x) -> soma de u(d), para cada divisor d de x
// l(1) = 1
// l(x) = 0, x > 1

// problemas iniciais:
// https://vjudge.net/problem/AtCoder-abc162_e
// https://vjudge.net/problem/CodeChef-SMPLSUM