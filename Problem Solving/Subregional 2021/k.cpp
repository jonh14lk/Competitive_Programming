#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, d, m;
  cin >> t >> d >> m;
  if (d < t)
  {
    cout << "N\n";
    return 0;
  }
  vector<int> v(m);
  for (int i = 0; i < m; i++)
    cin >> v[i];
  sort(v.begin(), v.end());
  v.pb(d);
  bool at = false;
  int sum = 0;
  int last = 0;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i] - last >= t)
      at = true;
    last = v[i];
  }
  (at) ? cout << "Y\n" : cout << "N\n";
  return 0;
}