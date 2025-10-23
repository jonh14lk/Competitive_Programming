#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k, l, r;
  cin >> n >> k >> l >> r;
  (k >= (n * l) && k <= (n * r)) ? cout << "S\n" : cout << "N\n";
  return 0;
}