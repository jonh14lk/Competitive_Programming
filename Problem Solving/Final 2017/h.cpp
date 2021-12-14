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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<int> v(3);
  for (int i = 0; i < 3; i++)
    cin >> v[i];
  int ans = 0;
  for (int i = 0; i < 3; i++)
  {
    int x;
    cin >> x;
    ans += max(0ll, x - v[i]);
  }
  cout << ans << endl;
  return 0;
}
