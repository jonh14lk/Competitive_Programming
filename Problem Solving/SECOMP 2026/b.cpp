
#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int k, n, m;
  cin >> k >> n >> m;
  int need = ceil((double)k / m);
  if (n >= need)
    cout << 0 << endl;
  else
    cout << need - n << endl;
}