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
#define MAXN 100005
#define mod 1000000007

int n;
int v[MAXN];

int dist(int a, int b)
{
  return (b - a + n) % n;
}
int calc(vector<int> v, int need)
{
  int n = v.size();
  deque<int> bigger;
  int ans = 0;
  for (int cnt = 0; cnt < 3; cnt++)
  {
    for (int i = 0; i < n; i++)
    {
      if (v[i] > need)
      {
        bigger.pb(i);
      }
      else if (v[i] < need)
      {
        while (bigger.size() && v[i] != need)
        {
          int x = bigger[0];
          int to = min(abs(need - v[x]), abs(need - v[i]));
          ans += (dist(x, i) * to);
          v[x] -= to;
          v[i] += to;
          if (v[x] == need)
            bigger.pop_front();
        }
      }
    }
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  vector<int> v(n);
  int sum = 0;
  for (int i = 0; i < n; i++)
    cin >> v[i], sum += v[i];
  int need = sum / n;
  int ans = calc(v, need);
  reverse(v.begin(), v.end());
  ans = min(ans, calc(v, need));
  cout << ans << endl;
  return 0;
}