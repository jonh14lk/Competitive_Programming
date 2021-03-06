#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int __int128
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000001
#define mod 998244353

int read() // __int128 functions
{
  int x = 0, f = 1;
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
void print(__int128 x) // __int128 functions
{
  if (x < 0)
  {
    cout << "-";
    x = -x;
  }
  stack<char> s;
  while (x)
  {
    s.push((x % 10) + '0');
    x = x / 10;
  }
  while (!s.empty())
  {
    cout << s.top();
    s.pop();
  }
}
namespace pollard_rho
{
  int multiplicate(int x, int y, int m)
  {
    return (x * y) % m;
  }
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
    if (x == 1 or x == n - 1)
      return false;
    for (int r = 1; r < s; r++)
    {
      x = multiplicate(x, x, n);
      if (x == n - 1LL)
        return false;
    }
    return true;
  };
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
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
      if (n == a)
        return true;
      if (is_composite(n, a, d, r))
        return false;
    }
    return true;
  }
  int f(int x, int m)
  {
    return multiplicate(x, x, m) + 1;
  }
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
signed main()
{
  //ios_base::sync_with_stdio(false);
  //cin.tie(NULL);
  while (1)
  {
    int n = read();
    if (n == 0)
      break;
    vector<int> factors = pollard_rho::fact(n);
    sort(factors.begin(), factors.end());
    int prev = -1, cnt = 0;
    for (auto const &i : factors)
    {
      if (prev != i)
      {
        if (prev != -1)
        {
          print(prev);
          printf("^");
          print(cnt);
          printf(" ");
        }
        prev = i;
        cnt = 0;
      }
      cnt++;
    }
    if (prev != -1)
    {
      print(prev);
      printf("^");
      print(cnt);
      printf(" ");
    }
    printf("\n");
  }
  return 0;
}
// sources:
// https://github.com/PauloMiranda98/Competitive-Programming-Notebook/blob/master/code/math/prime.h
// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/pollardrho.cpp
// fast integer factorization with pollard-rho
// https://www.spoj.com/problems/FACT0/ - ok
// https://www.spoj.com/problems/FACT1/ - ok
// https://www.spoj.com/problems/FACT2/ - sigkill
// since the limit is at most 29 digits(in FACT2), we need to use __int128
