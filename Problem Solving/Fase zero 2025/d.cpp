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
#define MAXN 1005
#define MAXK 8005

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  string s, t;
  cin >> s >> t;
  int tot = 0, tot2 = 0;
  for (int i = 0; i < n; i++)
  {
    if (s[i] == '*')
    {
      tot++;
      tot2 += (t[i] != '*');
    }
    else
    {
      assert(t[i] == s[i]);
    }
  }
  double ans = (double)tot2 / tot;
  cout << fixed << setprecision(2) << ans << endl;
  return 0;
}
