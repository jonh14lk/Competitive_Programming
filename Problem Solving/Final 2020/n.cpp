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
#define MAXN 100005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  char c;
  double x;
  cin >> c >> x;
  int sum = x * 100, ans = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> c >> x;
    x *= 100;
    sum += x;
    if (sum % 100)
      ans++;
  }
  cout << ans << endl;
  return 0;
}