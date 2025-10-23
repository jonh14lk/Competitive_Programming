#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n1, n2, n12;
  cin >> n1 >> n2 >> n12;
  cout << ((n1 + 1) * (n2 + 1)) / (n12 + 1) - 1 << endl;
  return 0;
}