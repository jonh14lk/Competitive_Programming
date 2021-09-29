#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  vector<int> vv(m);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < m; i++)
    cin >> vv[i];
  int ans = 0, prev = LLONG_MAX, curr = 0;
  for (int l = 0, r = 0; l < m; l++)
  {
    if (vv[l] != prev)
      curr = 0;
    while (r < n && v[r] <= vv[l])
    {
      if (v[r] == vv[l])
        curr++;
      r++;
    }
    ans += curr;
    prev = vv[l];
  }
  cout << ans << endl;
}
//You are given two arrays a and b, sorted in non-decreasing order. Find the number of pairs (i,j) for which ai=bj.
