#include <bits/stdc++.h>
using namespace std;

#define fir first
#define sec second
#define int __int128
#define pi pair<int, int>

namespace pollard_rho
{
  int multiplicate(int x, int y, int m) { return (x * y) % m; }
  int modpow(int x, int y, int m)
  {
    int z = 1;
    while (y)
    {
      if (y & 1)
        z = (z * x) % m;
      x = (x * x) % m;
      y >>= 1;
    }
    return z;
  }

  bool is_composite(int n, int a, int d, int s)
  {
    int x = modpow(a, d, n);
    if (x == 1 or x == n - 1LL)
      return false;
    for (int r = 1; r < s; r++)
    {
      x = multiplicate(x, x, n);
      if (x == n - 1LL)
        return false;
    }
    return true;
  }

  int miller_rabin(int n)
  {
    if (n < 2)
      return false;
    int r = 0, d = n - 1LL;
    while ((d & 1LL) == 0)
    {
      d >>= 1;
      r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 27})
    {
      if (n == a)
        return true;
      if (is_composite(n, a, d, r))
        return false;
    }
    return true;
  }

  int f(int x, int m) { return multiplicate(x, x, m) + 1LL; }

  int rho(int n)
  {
    int x0 = 1, t = 0, prd = 2;
    int x = 0, y = 0, q;
    while (t % 40 || __gcd(prd, n) == 1)
    {
      if (x == y)
      {
        x0++;
        x = x0;
        y = f(x, n);
      }
      q = multiplicate(prd, max(x, y) - min(x, y), n);
      if (q != 0)
        prd = q;
      x = f(x, n);
      y = f(y, n);
      y = f(y, n);
      t++;
    }
    return __gcd(prd, n);
  }

  vector<int> fact(int n)
  {
    if (n == 1)
      return {};
    if (miller_rabin(n))
      return {n};
    int x = rho(n);
    auto l = fact(x), r = fact(n / x);
    l.insert(l.end(), r.begin(), r.end());
    return l;
  }
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

map<int, int> ans;
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;

  int num = 0;
  for (int i = 0; i < min((int)13, (int)s.size()); i++)
  {
    num *= 10;
    num += (s[i] - '0');
  }
  auto vet = pollard_rho::fact(num);
  for (auto x : vet)
    ans[x]++;

  if (s.size() <= 13)
  {
    cout << ans.size() << '\n';
    for (auto x : ans)
    {
      print(x.first);
      cout << ' ';
      print(x.second);
      cout << '\n';
    }
  }
  else
  {
    for (int i = 13; i < s.size(); i++)
    {
      ans[2]++;
      ans[5]++;
    }
    cout << ans.size() << '\n';
    for (auto x : ans)
    {
      print(x.first);
      cout << ' ';
      print(x.second);
      cout << '\n';
    }
  }
}