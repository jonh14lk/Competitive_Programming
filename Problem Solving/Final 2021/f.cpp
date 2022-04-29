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
#define MAXN 300001
#define mod 1000000007

int ans[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN];

void dfs(int s)
{
  ans[s] = 2;
  vis[s] = 1;
  for (auto const &i : adj[s])
  {
    if (!vis[i] && ans[i] != 1)
      dfs(i);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  ans[n - 1] = 1;
  ans[n - 2] = 2;
  dfs(n - 2);
  for (int i = 0; i < n; i++)
    (ans[i] == 2) ? cout << "B" : cout << "A";
  cout << endl;
  return 0;
}