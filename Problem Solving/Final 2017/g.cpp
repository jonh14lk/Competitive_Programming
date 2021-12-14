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
#define MAXN 100007
#define mod 1000000007

int n;
vector<int> adj[MAXN];
int type[MAXN];
int dp[MAXN][2][2]; // indice / eh verdadeiro / valor
int tab[2][2];

void dfs(int i)
{
  if (i == 0) // nao existe
  {
    dp[i][1][1] = 1;
    dp[i][1][0] = 1;
    dp[i][0][1] = 0;
    dp[i][0][0] = 0;
    return;
  }
  for (auto const &j : adj[i])
  {
    dfs(j);
  }
  int l = adj[i][0], r = adj[i][1];
  for (int a = 0; a < 2; a++)
  {
    for (int b = 0; b < 2; b++)
    {
      for (int c = 0; c < 2; c++)
      {
        for (int d = 0; d < 2; d++)
        {
          int res = (type[i] == -1) ? tab[b][d] : type[i];
          int true_b = (!a) ? (b ^ 1) : b;
          int true_d = (!c) ? (d ^ 1) : d;
          int ok = (tab[true_b][true_d] == res) ? 1 : 0;
          int to_add = (dp[l][a][b] * dp[r][c][d]) % mod;
          dp[i][ok][res] = (dp[i][ok][res] + to_add) % mod;
        }
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  tab[0][0] = 1;
  tab[0][1] = 1;
  tab[1][0] = 1;
  tab[1][1] = 0;
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      int x;
      cin >> x;
      adj[i].pb(x);
    }
    cin >> type[i];
  }
  dfs(1);
  int ans = (dp[1][0][1] + dp[1][0][0]) % mod;
  cout << ans << endl;
  return 0;
}
