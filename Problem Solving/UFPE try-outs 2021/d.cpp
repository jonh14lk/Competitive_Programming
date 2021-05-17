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
#define MAXN 5001
#define mod 1000000007

int query(int l, int r)
{
  cout << l + 1 << " " << r + 1 << endl;
  fflush(stdout);
  int ans;
  cin >> ans;
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int l = 0, r = n - 1;
  while (l < r)
  {
    int mid = (l + r) >> 1;
    (query(0, mid)) ? r = mid : l = mid + 1;
  }
  cout << "! " << l + 1 << endl;
  fflush(stdout);
  return 0;
}