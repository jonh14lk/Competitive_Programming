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
  int n;
  cin >> n;
  if (n == 1)
  {
    cout << "N\n";
    return 0;
  }
  vector<int> p;
  while (n % 2 == 0)
  {
    p.pb(2);
    n = n / 2;
  }
  for (int i = 3; i <= sqrt(n); i += 2)
  {
    while (n % i == 0)
    {
      p.pb(i);
      n = n / i;
    }
  }
  if (n > 2)
  {
    p.pb(n);
  }
  sort(p.begin(), p.end());
  if (p.size() == 2 && p[0] != p[1])
    cout << "Y\n";
  else if (p[0] == p.back() && (p.size() % 2) == 1)
    cout << "Y\n";
  else
    cout << "N\n";
}