#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, x;
  cin >> a >> x;
  for (int y = 2; y <= (a + 1); y++)
  {
    if ((x * y) % a == 1)
    {
      cout << y << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}