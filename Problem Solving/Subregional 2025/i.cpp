#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pi> v(n);
  vector<int> dist(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    if (i > 0)
    {
      dist[i] = abs(v[i].fir - v[i - 1].fir) + abs(v[i].sec - v[i - 1].sec);
    }
  }
  pi r = {0, 1};
  vector<pi> restr(n - 1);
  restr[0] = r;
  for (int i = 1; i < n; i++)
  {
    r.sec ^= 1;
    r.fir *= -1;
    r.fir += dist[i];
    restr[i - 1] = r;
  }
  pi ans = {1, 1e18};
  for (auto const &i : restr)
  {
    if (i.sec == 0) // restricao do tipo i.fir - r1 >= 1
    {
      ans.sec = min(ans.sec, i.fir - 1ll); // r1 <= i.fir - 1
    }
    else // restricao do tipo i.fir + r1 >= 1
    {
      ans.fir = max(ans.fir, 1ll - i.fir); // r1 >= 1 - i.fir
    }
  }
  if (ans.fir > ans.sec)
    cout << "-1\n";
  else
    cout << ans.sec << endl;
  return 0;
}
// r1
// dist[1] - r1
// dist[2] - dist[1] + r1
// dist[3] - dist[2] + dist[1] - r1