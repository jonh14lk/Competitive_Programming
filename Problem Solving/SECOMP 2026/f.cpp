
#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int n;
  cin >> n;
  int sums = 0;
  bool has_mul_67 = false;
  for (int i = 0; i < n; i++)
  {
    char c;
    int x;
    cin >> c >> x;
    if (c == '+')
      sums += x;
    else if (c == '*' && x == 67)
      has_mul_67 = true;
  }
  if (sums == 67)
  {
    cout << "SIM\n";
  }
  else if (sums == 1 && has_mul_67)
  {
    cout << "SIM\n";
  }
  else
  {
    cout << "NAO\n";
  }
}