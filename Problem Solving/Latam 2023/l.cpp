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
#define MAXN 1005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int r, c, k;
  cin >> r >> c >> k;
  for (int i = 0; i < r; i++)
  {
    string s, t;
    cin >> s >> t;
    bool has = 0;
    for (int j = 0; j < k; j++)
    {
      if (t[j] == '*')
        has = 1;
    }
    if (has)
    {
      for (int j = 0; j < c; j++)
      {
        if (s[j] != '*')
        {
          cout << "N\n";
          return 0;
        }
      }
    }
  }
  cout << "Y\n";
}