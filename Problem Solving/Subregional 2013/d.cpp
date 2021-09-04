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

vector<int> ans;

vector<int> dobra(vector<int> &v, int pos)
{
  vector<int> curr;
  int l = pos, r = pos + 1;
  while (l >= 0 || r < v.size())
  {
    int ll = (l >= 0) ? v[l] : 0;
    int rr = (r < v.size()) ? v[r] : 0;
    curr.pb(ll + rr);
    l--, r++;
  }
  reverse(curr.begin(), curr.end());
  return curr;
}
int solve(vector<int> v)
{
  if (v.size() <= ans.size())
  {
    if (ans == v)
      return true;
    reverse(v.begin(), v.end());
    return (ans == v);
  }
  for (int i = 0; i < v.size() - 1; i++)
    if (solve(dobra(v, i)))
      return true;
  return false;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int m;
  cin >> m;
  ans.resize(m);
  for (int i = 0; i < m; i++)
    cin >> ans[i];
  (solve(v)) ? cout << "S\n" : cout << "N\n";
  return 0;
}