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
#define MAXN 10005
#define mod 1000000007

int n;
vector<pi> v;
double dp[MAXN];

double solve(int i)
{
  if (i == n)
    return 0;
  if (dp[i] != -1)
    return dp[i];
  double sum = v[i].sec;
  int sum2 = v[i].fir;
  double ret = sum + solve(i + 1);
  for (int x = i + 1; x <= i + 5; x++)
  {
    if (x >= n)
      break;
    if (sum2 >= 120)
      break;
    if (x == i + 1)
      sum += (0.5 * v[x].sec);
    else
      sum += (0.25 * v[x].sec);
    double curr = sum + solve(x + 1);
    ret = min(ret, curr);
    sum2 += v[x].fir;
  }
  return dp[i] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    v.pb({a, b});
  }
  for (int i = 0; i <= n; i++)
  {
    dp[i] = -1;
  }
  cout << setprecision(2) << fixed << solve(0) << endl;
  return 0;
}