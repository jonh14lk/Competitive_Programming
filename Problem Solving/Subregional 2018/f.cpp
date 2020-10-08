#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 2001
#define mod 1000000007
#define INF 1e7 * -1

struct palco
{
  int l, r, c, p;
};

int n;
vector<palco> v;
int dp[1003][1024];
int to[1001];
int pot[11];

bool cmp(palco a, palco b)
{
  if (a.l != b.l)
    return a.l < b.l;
  a.r < b.r;
}
int solve(int i, int j)
{
  if (i == v.size())
    return dp[i][j] = (j == (pot[n] - 1)) ? 0 : INF;
  if (dp[i][j] != -1)
    return dp[i][j];
  return dp[i][j] = max(solve(i + 1, j), v[i].c + solve(to[i], j | pot[v[i].p]));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++)
    {
      int a, b, c;
      cin >> a >> b >> c;
      v.pb({a, b, c, i});
    }
  }
  int currpot = 1;
  for (int i = 0; i <= 10; i++)
  {
    pot[i] = currpot;
    currpot = currpot << 1;
  }
  sort(v.begin(), v.end(), cmp);
  for (int i = 0; i < v.size(); i++)
    to[i] = v.size();
  for (int i = 0; i < v.size(); i++)
  {
    for (int j = i + 1; j < v.size(); j++)
    {
      if (v[j].l >= v[i].r)
      {
        to[i] = j;
        break;
      }
    }
  }
  memset(dp, -1, sizeof(dp));
  int ans = solve(0, 0);
  (ans >= 0) ? cout << ans << endl : cout << -1 << endl;
}