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

const int LIM = 1e17;

vector<int> v;
unordered_map<int, int> dp;
unordered_map<int, int> choose;
unordered_map<int, int> vis;

int solve(int n)
{
  if (n == 1)
    return 1;
  if (vis[n])
    return dp[n];
  int ret = 0;
  for (int i = v.size() - 1; i >= 0; i--)
  {
    if (n % v[i] == 0)
    {
      int curr = solve(n / v[i]);
      if (curr == 1)
      {
        vis[n] = true;
        choose[n] = v[i];
        return dp[n] = 1;
      }
    }
  }
  vis[n] = true;
  return dp[n] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  v.clear();
  v.pb(2);
  v.pb(3);
  while (1)
  {
    int n = v.size();
    int x = v[n - 1] + v[n - 2];
    if (x <= LIM)
      v.pb(x);
    else
      break;
  }
  int n;
  cin >> n;
  if (solve(n) == 0)
  {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  vector<int> ans;
  while (n > 1)
  {
    ans.pb(choose[n]);
    n /= choose[n];
  }
  string s;
  for (auto const &i : ans)
  {
    int idx = lower_bound(v.begin(), v.end(), i) - v.begin();
    string t = "";
    for (int j = 0; j <= idx; j++)
      t.pb('A');
    t.pb('B');
    s += t;
  }
  cout << s << endl;
  return 0;
}