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
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int l = 0, r = 0, ll = 0, rr = 0, t = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == 'S')
    {
      (t) ? rr++ : ll++;
    }
    else if (s[i] == 'R')
    {
      (!t) ? rr++ : ll++;
      t = !t;
    }
    else
    {
      if (l == 2 || r == 2)
      {
        if (l == 2)
          cout << l << " (winner) - " << r << endl;
        else
          cout << l << " - " << r << " (winner)\n";
      }
      else
      {
        if (t)
          cout << l << " (" << ll << ") - " << r << " (" << rr << "*)" << endl;
        else
          cout << l << " (" << ll << "*) - " << r << " (" << rr << ")" << endl;
      }
    }
    if (ll == 10 || (ll >= 5 && ll - rr >= 2))
      l++, ll = 0, rr = 0;
    if (rr == 10 || (rr >= 5 && rr - ll >= 2))
      r++, ll = 0, rr = 0;
  }
  return 0;
}