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

int gcd(int a, int b, int &x, int &y)
{
  if (b == 0)
  {
    x = 1;
    y = 0;
    return a;
  }
  int x1, y1;
  int d = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
signed main()
{
  int n;
  cin >> n;
  int k = 2;
  while (1)
  {
    int x, y;
    if (gcd(k, n, x, y) == 1)
    {
      x = ((x % n) + n) % n;
      cout << x << endl;
      return 0;
    }
    k++;
  }
  return 0;
}
// achar os numeros x e y tal que:
// a * x + b * y = gcd(a, b)

// problema exemplo:
// https://codeforces.com/group/btcK4I5D5f/contest/451372/problem/J
// dado um numero k
// quero achar um numero x, se possivel, tal que:
// (k * x) % n = 1

// k * x + n * y = 1
// se gcd(k, n) = 1, então:
// k * x + n * y = gcd(k, n)
// note que, se gcd(k, n) > 1, logo nao existe solução