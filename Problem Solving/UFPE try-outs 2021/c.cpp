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

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k, q;
  cin >> n >> k >> q;
  string s, t;
  cin >> s >> t;
  reverse(s.begin(), s.end());
  for (int i = 0; i < q; i++)
  {
    string tt = "";
    for (int j = 0; j < n; j++)
    {
      deque<char> curr;
      curr.pb(t[j]);
      int l = (j - 1 + n) % n;
      int r = (j + 1) % n;
      for (int f = 0; f < k; f++)
      {
        curr.push_front(t[l]);
        curr.push_back(t[r]);
        l = (l - 1 + n) % n;
        r = (r + 1) % n;
      }
      reverse(curr.begin(), curr.end());
      int bit = 0, num = 0;
      for (auto const &i : curr)
      {
        if (i == '1')
          num += (1LL << bit);
        bit++;
      }
      tt += s[num];
    }
    t = tt;
  }
  cout << t << endl;
  return 0;
}