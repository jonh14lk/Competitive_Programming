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
#define MAXN 2405
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  vector<int> ans;
  ans.pb(1);
  for (int i = 0; i < s.size() - 1; i++)
  {
    if (s[i] != s[i + 1])
    {
      ans.pb(0);
      vector<int> prev = ans;
      for (int j = ans.size() - 1; j >= 0; j--)
        ans[j] = ((2 * i) + 3) * -1 * ans[j];
      for (int j = ans.size() - 1; j > 0; j--)
        ans[j] += prev[j - 1];
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans.size() - 1 << endl;
  for (auto const &i : ans)
    (s.back() == 'A') ? cout << i * -1 << " " : cout << i << " ";
  cout << endl;
  return 0;
}