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
#define MAXN 300005

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int st = -1, to_go = 0;
  vector<int> nxt;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    if (a > to_go)
    {
      if (nxt.size())
      {
        st ^= 1;
        to_go += 10;
        nxt.clear();
      }
      else
      {
        st = -1;
      }
    }
    if (st == -1 || st == b)
    {
      st = b;
      to_go = a + 10;
    }
    else
    {
      nxt.pb(a);
    }
  }
  if (nxt.size())
  {
    to_go += 10;
    nxt.clear();
  }
  cout << to_go << endl;
  return 0;
}