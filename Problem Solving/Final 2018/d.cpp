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
#define MAXN 100005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  set<string> s;
  for (int i = 0; i < n; i++)
  {
    string t;
    cin >> t;
    string c;
    int flag = 0;
    for (auto const &j : t)
    {
      if (j == '@')
        flag = 2;
      else if (j == '+' && flag == 0)
        flag = 1;
      else if (j == '.' && flag == 0)
        continue;
      else if (flag != 1)
        c.pb(j);
    }
    s.insert(c);
  }
  cout << s.size() << endl;
}