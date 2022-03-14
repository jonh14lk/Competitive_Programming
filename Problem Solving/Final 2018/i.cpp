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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

vector<int> adj[MAXN];
int dp[MAXN][4];
bool vis[MAXN][4];

int solve(int i, int j)
{
  if (vis[i][j])
    return dp[i][j];
  int ret = 0;
  if (j == 0)
  {
    int sum = 0;
    for (auto const &k : adj[i])
    {
      sum += max(solve(k, 0), solve(k, 1));
    }
    ret = max(ret, sum);
  }
  else if (j == 1)
  {
    if (adj[i].size() < 3)
    {
      return dp[i][j] = -1e15;
    }
    // escolher 2 zeros
    // escolher um 2
    // o resto pode ser 0 ou 1
    set<pi> profit;
    map<int, int> c;
    map<int, int> best;
    int sum = 0;
    for (auto const &k : adj[i])
    {
      c[k] = solve(k, 1) - solve(k, 0);
      best[k] = max(solve(k, 0), solve(k, 1));
      sum += best[k];
      profit.insert({c[k], k});
    }
    for (auto const &k : adj[i])
    {
      vector<int> todo;
      int curr = sum;
      curr -= best[k];
      curr += solve(k, 2);
      todo.pb(k);
      profit.erase({c[k], k});
      for (int _ = 0; _ < 2; _++)
      {
        int x = (*profit.begin()).sec;
        curr -= best[x];
        curr += solve(x, 0);
        todo.pb(x);
        profit.erase({c[x], x});
      }
      ret = max(ret, curr);
      for (auto const &_ : todo)
      {
        profit.insert({c[_], _});
      }
    }
  }
  else if (j == 2)
  {
    // escolher 2 zeros
    // o resto pode ser 0 ou 1
    if (adj[i].size() < 2)
    {
      return dp[i][j] = -1e15;
    }
    int sum = 1;
    vector<pi> profit;
    for (auto const &k : adj[i])
    {
      int x = solve(k, 1) - solve(k, 0);
      profit.pb({x, k});
    }
    sort(profit.begin(), profit.end());
    for (int k = 0; k < 2; k++)
    {
      int x = profit[k].sec;
      sum += solve(x, 0);
    }
    for (int k = 2; k < profit.size(); k++)
    {
      int x = profit[k].sec;
      sum += max(solve(x, 0), solve(x, 1));
    }
    ret = sum;
  }
  vis[i][j] = 1;
  return dp[i][j] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int p;
    cin >> p;
    p--;
    adj[p].pb(i);
  }
  cout << solve(0, 0) << endl;
  return 0;
}