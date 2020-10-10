#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 11

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int v, n;
  cin >> v >> n;
  double i = 10;
  while (i <= 90)
  {
    double k = (n * v * i) / 100;
    int ans = ceil(k);
    cout << ans << " ";
    i += 10.0;
  }
  cout << endl;
  return 0;
}