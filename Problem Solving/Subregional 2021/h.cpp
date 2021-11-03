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
  int n, k;
  cin >> n >> k;
  vector<pi> v(n);
  vector<pi> o(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    o[i] = v[i];
  }
  sort(v.begin(), v.end());
  bool can = true;
  for (int i = 0; i < n; i++)
    if (v[i].sec != o[i].sec)
      can = false;
  (can) ? cout << "Y\n" : cout << "N\n";
  return 0;
}