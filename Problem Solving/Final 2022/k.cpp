#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 1000000007
#define INF 1e9

int v[102][102];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int ans = 0;
  while ((1 << ans) < n)
    ans++;
  cout << ans << endl;
  int cnt = 1, x = 0;
  for (int i = 1; i <= 100; i++)
  {
    for (int j = 1; j <= 100; j++)
    {
      if (i % 2 || j == 100 || cnt >= n)
        v[i][j] = (1 << ans) - 1;
      else
        v[i][j] = x++, cnt++;
    }
  }
  for (int b = 0; b < ans; b++)
  {
    vector<pi> curr;
    for (int i = 1; i <= 100; i++)
    {
      for (int j = 1; j <= 100; j++)
      {
        if (v[i][j] & (1 << b))
          curr.pb({i, j});
      }
    }
    cout << curr.size() << " ";
    for (auto const &i : curr)
      cout << i.fir << " " << i.sec << " ";
    cout << endl;
  }
}