#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 5001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<int> v(3);
  cin >> v[0] >> v[1] >> v[2];
  int ans = LLONG_MAX;
  for (int i = 0; i < 3; i++)
  {
    int curr = 0;
    for (int j = 0; j < 3; j++)
      curr += (abs(i - j) * v[j] * 2);
    ans = min(ans, curr);
  }
  cout << ans << endl;
}