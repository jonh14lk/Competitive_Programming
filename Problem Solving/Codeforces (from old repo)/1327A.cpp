#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int q;
  cin >> q;
 
  while (q--)
  {
    lli a, b;
    cin >> a >> b;
 
    if (a % 2 == 0 && b % 2 == 0 && a / b >= b)
    {
      cout << "YES\n";
    }
    else if (a % 2 != 0 && b % 2 != 0 && a / b >= b)
    {
      cout << "YES\n";
    }
    else if (a == 1 && b == 1)
    {
      cout << "YES\n";
    }
    else
    {
      cout << "NO\n";
    }
  }
  return 0;
}
