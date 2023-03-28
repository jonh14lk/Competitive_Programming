#include <bits/stdc++.h>
using namespace std;
#define int long long

#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define pb push_back

int n, p, h;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> p >> h;
  int hh = h;
  vector<int> ans; // 1 contra, 0 a favor
  vector<char> ans2(n);
  for (int i = n; i >= 1; i--)
  {
    int k = 1ll << i;
    if (hh > k / 2)
    {
      ans.pb(1);
      hh = k - hh + 1;
    }
    else
    {
      ans.pb(0);
    }
  }
  reverse(ans.begin(), ans.end());
  int v = 1ll << n;
  for (int i = 0; i < n; i++)
  {
    if (ans[i])
    {
      if (p > v / 2)
      {
        ans2[i] = 'R';
        p = v - p + 1;
      }
      else
      {
        ans2[i] = 'L';
        p = v / 2 - p + 1;
      }
      v >>= 1;
    }
    else
    {
      if (p > v / 2)
      {
        ans2[i] = 'L';
        p = p - v / 2;
      }
      else
      {
        ans2[i] = 'R';
      }
      v >>= 1;
    }
    cout << ans2[i];
  }
  cout << endl;
  return 0;
}