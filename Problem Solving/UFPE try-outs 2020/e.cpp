#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<string, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 2000001
#define MAXL 20
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    if (n >= 8128)
      cout << "8128\n";
    else if (n >= 496)
      cout << "496\n";
    else if (n >= 28)
      cout << "28\n";
    else if (n >= 6)
      cout << "6\n";
    else
      cout << "-1\n";
  }
  return 0;
}