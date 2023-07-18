#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200001
#define mod 998244353

int lpf[MAXN];
int mobius[MAXN];
int mp[MAXN];
vector<int> d[MAXN];

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
void calc()
{
  for (int i = 2; i < MAXN; i++) // divisores
  {
    for (int j = i; j < MAXN; j += i)
      d[j].pb(i);
  }
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
void add(int x, int dd) // adiciona dd em todos os val[i] que gcd(x, i) > 1
{
  for (auto const &i : d[x])
    mp[i] += dd;
}
int sum(int x) // valor de val[x]
{
  int ans = 0;
  for (auto const &i : d[x])
    ans += (mobius[i] * -1 * mp[i]);
  return ans;
}
signed main()
{
  return 0;
}
// mobius/inclusao-exclusao com os fatores primos
// a função de mobius eh definida como:
// mi(n) = 1, se n é um square-free com um numero par de fatores primos
// mi(n) = -1, se n é um square-free com um numero impar de fatores primos
// mi(n) = 0, caso nenhum dos dois
// square-free = nenhum fator primo aparece duas vezes ou mais

// dai pra problemas que da pra se fazer com inclusao-exclusao nos fatores primos
// também sai com mobius