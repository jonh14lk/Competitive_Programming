#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007
#define inf 1e9

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, c, k;
  cin >> t >> c >> k;
  cout << min(c, k * t) << endl;
  return 0;
}