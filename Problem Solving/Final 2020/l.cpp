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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005
#define mod 1000000007

bool vis[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, x;
  cin >> n >> x;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    for (int i = a; i <= a + b; i++)
      vis[i] = true;
  }
  int ans = -1, c = INT_MAX;
  for (int i = 0; i <= 480; i++)
  {
    int t = i, cc = 0;
    while (t < MAXN)
    {
      if (vis[t])
        cc++;
      t += x;
    }
    if (cc < c)
    {
      c = cc;
      ans = i;
    }
  }
  cout << ans << " " << c << endl;
  return 0;
}
// tomar a cada x minutos
// t[0]
// 8