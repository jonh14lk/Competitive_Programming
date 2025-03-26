#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 1000000007

const int inf = 1e9;

int n;
string s[MAXN];
int dp[MAXN][3];

bool is(char c)
{
  return (c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U' && c != 'Y');
}
int solve(int i, int j)
{
  if (i == n)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ans = inf, cons = j;
  for (int x = 1; x <= min((int)s[i].size(), 3); x++)
  {
    if (is(s[i][x - 1]))
      cons++;
    else
      cons = 0;
    if (cons <= 2)
      ans = min(ans, x + solve(i + 1, cons));
    else
      break;
  }
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> s[i];
  memset(dp, -1, sizeof(dp));
  int ans = solve(0, 0);
  (ans >= inf) ? cout << "*\n" : cout << ans << endl;
}