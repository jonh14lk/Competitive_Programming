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
#define mod 998244353

namespace min_queue
{
  deque<pi> q;
  int l, r;

  void init()
  {
    l = r = 1;
    q.clear();
  }
  void push(int v)
  {
    while (!q.empty() && v < q.back().fir)
      q.pop_back();
    q.pb({v, r});
    r++;
  }
  void pop()
  {
    if (!q.empty() && q.front().sec == l)
      q.pop_front();
    l++;
  }
  int getmin()
  {
    return q.front().fir;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int l = 0, r = m - 1;
  cout << l << " " << r << endl;
  for (int i = l; i <= r; i++)
    min_queue::push(v[i]);
  cout << min_queue::getmin() << " ";
  l++, r++;
  while (r < n)
  {
    min_queue::pop();
    min_queue::push(v[r]);
    cout << min_queue::getmin() << " ";
    l++, r++;
  }
  cout << endl;
  return 0;
}
// minimum of each subarray of length m (m <= n)
