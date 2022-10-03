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

vector<int> adj[64];

int msb(int x)
{
  for (int i = 63; i >= 0; i--)
  {
    if (x & (1ll << i))
      return i;
  }
  return 0;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    if (x > 0)
      adj[msb(x)].pb(x);
  }
  vector<int> ans;
  for (int i = 63; i >= 0; i--)
  {
    if (adj[i].size() > 0)
    {
      int x = adj[i].back();
      adj[i].pop_back();
      ans.pb(x);
      for (auto const &j : adj[i])
      {
        int y = j ^ x;
        if (y > 0)
          adj[msb(y)].pb(y);
      }
      adj[i].clear();
    }
  }
  int x = 0;
  for (auto const &i : ans)
  {
    int curr = x ^ i;
    x = max(x, curr);
  }
  cout << x << endl;
  return 0;
}