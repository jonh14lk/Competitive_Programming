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
#define DEBUG 0
#define MAXN 5001
#define mod 1000000007

int n;
vector<int> v;

int modpow(int x, int y)
{
  int z = 1;
  while (y)
  {
    if (y & 1)
      z = (z * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return z;
}
int inverse(int x)
{
  return modpow(x, mod - 2);
}
int divide(int x, int y)
{
  return (x * inverse(y)) % mod;
}
int subtract(int x, int y)
{
  return ((x + mod) - y) % mod;
}
int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int sum(int x, int y)
{
  return (x + y) % mod;
}

namespace sh
{
  const int d = 31;
  vector<int> pot;
  vector<int> pref;
  vector<int> suf;

  void calc()
  {
    pot.resize(n + 1);
    pot[0] = 1;
    for (int i = 1; i <= n; i++)
      pot[i] = multiplicate(pot[i - 1], d);
  }
  void suffix_hash()
  {
    suf.resize(n + 1);
    suf[0] = 0;
    for (int i = 0; i < n; i++)
    {
      int val = multiplicate(v[n - i - 1], pot[i]);
      suf[i + 1] = sum(suf[i], val);
    }
  }
  void prefix_hash()
  {
    pref.resize(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; i++)
    {
      int val = multiplicate(v[i], pot[i]);
      pref[i + 1] = sum(pref[i], val);
    }
  }
  int prefix(int l, int r)
  {
    return divide(subtract(pref[r + 1], pref[l]), pot[l]);
  }
  int suffix(int l, int r)
  {
    return divide(subtract(suf[n - l], suf[n - r - 1]), pot[n - r - 1]);
  }
} // namespace sh
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  n = s.size();
  for (auto const &i : s)
    v.pb((i - 'a') + 1);                // indexar a partir do 1
  sh::calc();                           // potencias de d
  sh::prefix_hash();                    // hashing dos prefixos de s
  cout << sh::prefix(0, n - 1) << endl; // resposta final
  return 0;
}
// string hashing
// podemos representar uma string como um valor inteiro
// seja s uma string e d o tamanho do alfabeto
// o valor de hashing de s eh igual a:
// (s[0] * pow(d, 0)) + (s[1] * pow(d, 1)) + ... (s[n - 1] * pow(d, n - 1))
// como esse valor pode ser gigantesco
// fazer isso com um modulo que for o maior possivel
// nesse caso usaremos 10^9 + 7
// logo o hashing fica:
// ((s[0] * pow(d, 0)) + (s[1] * pow(d, 1)) + ... (s[n - 1] * pow(d, n - 1))) % mod
// o hashing possui diversas aplicacoes como:
// checar substring que sao palindromas
// numeros de substrings diferentes em uma string
// etc...
