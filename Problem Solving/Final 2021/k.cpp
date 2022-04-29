#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pbc push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 3000001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  map<char, bool> vis;
  vector<string> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    vis[v[i][0]] = 1;
  }
  for (auto const &i : v)
  {
    bool ok = 1;
    for (auto const &j : i)
    {
      if (!vis[j])
      {
        ok = 0;
        break;
      }
    }
    if (ok)
    {
      cout << "Y\n";
      return 0;
    }
  }
  cout << "N\n";
  return 0;
}