
#include <bits/stdc++.h>
using namespace std;

#define int long long int

int f(int a, int b, int n)
{
  if (a == (n + 1) / 2 || b == (n + 1) / 2)
    return 1;
  return f(a + 1, b, n) + f(a, b + 1, n);
}
signed main()
{
  int n;
  cin >> n;
  cout << f(0, 0, n) << endl;
}