#include <bits/stdc++.h>
using namespace std;

#define int __int128
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

__int128 read()
{
  __int128 x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(__int128 x)
{
  if (x < 0)
  {
    cout << "-";
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  char at = (x % 10) + '0';
  cout << at;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, s, l, r;
  a = read();
  s = read();
  l = read();
  r = read();
  int ans = (a == s) ? 1 : 0;
  for (int d = 1; d <= (r - l); d++)
  {
    // aqui temos que chutar o termo inicial
    // sabemos a razao
    // entao a pa eh definida unicamente
    // os numeros que x <= a
    // (x % d) = (a % d)
    // x, x + d, x + 2d, ..., a
    vector<int> ini, fim;
    __int128 x = a;
    while (x >= l)
    {
      ini.pb(x);
      x -= d;
    }
    x = a;
    while (x <= r)
    {
      fim.pb(x);
      x += d;
    }
    reverse(ini.begin(), ini.end());
    auto sum = [&](int a1, int an)
    {
      __int128 n = ((an - a1) / d) + 1;
      __int128 ans = ((a1 + an) * n) / 2;
      return ans;
    };
    int j = 0;
    for (auto const &i : ini)
    {
      while (j < fim.size() && sum(i, fim[j]) < s)
        j++;
      if (j < fim.size() && sum(i, fim[j]) == s && i != fim[j])
        ans++;
    }
  }
  print(ans);
  cout << endl;
  return 0;
}
// razao eh no maximo r - l + 1