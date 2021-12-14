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
#define MAXN 1005
#define mod 1000000007

int n;
string s;
int dp[MAXN][MAXN];
int choose[MAXN][MAXN];

int solve(int i, int j)
{
  if (i == s.size())
    return (j == 0) ? 1 : 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ret = 0;
  for (int d = 0; d <= 9; d++)
  {
    if (i == 0 && d == 0)
      continue;
    if (s[i] == d + '0' || s[i] == '?')
    {
      int nxt = ((j * 10) + d) % n;
      int curr = solve(i + 1, nxt);
      if (curr > ret)
      {
        choose[i][j] = d;
        ret = curr;
      }
    }
  }
  return dp[i][j] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s >> n;
  memset(dp, -1, sizeof(dp));
  if (!solve(0, 0))
  {
    cout << "*\n";
    return 0;
  }
  int i = 0, j = 0;
  while (i < s.size())
  {
    cout << choose[i][j];
    int nxt = ((j * 10) + choose[i][j]) % n;
    i++;
    j = nxt;
  }
  cout << endl;
  return 0;
}
