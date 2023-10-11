#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  vector<int> b(n);
  for (int i = 0; i < n; i++)
    cin >> b[i];
  sort(a.begin(), a.end());
  sort(b.rbegin(), b.rend());
  vector<int> c;
  for (int i = 0; i < n; i++)
    c.pb(a[i] + b[i]);
  int ans = *max_element(c.begin(), c.end()) - *min_element(c.begin(), c.end());
  cout << ans << endl;
  return 0;
}