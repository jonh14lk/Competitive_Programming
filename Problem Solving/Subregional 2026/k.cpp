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

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> a(n);
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    sum += a[i];
  }
  vector<int> b(n);
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
    if (b[i] > a[i])
    {
      cout << "-1\n";
      return 0;
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    ans = max(ans, sum - a[i] + b[i]);
  }
  cout << ans << endl;
  return 0;
}