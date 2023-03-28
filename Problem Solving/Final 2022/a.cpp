#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define inf long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 1000000007

int a, b, ii;
pi v[MAXN];
bool vis[MAXN];
int mask[MAXN];
vector<int> adj[MAXN];

void dfs(int x, int val)
{
  vis[x] = 1;
  mask[x] |= val;
  for (auto const &y : adj[x])
  {
    if (!vis[y] && y != ii)
      dfs(y, val);
  }
}
void dfs2(int x, int val)
{
  vis[x] = 1;
  mask[x] |= val;
  for (auto const &y : adj[x])
  {
    if (!vis[y])
      dfs(y, val);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    v[i] = {a, b};
    adj[a].pb(i);
    adj[b].pb(i);
  }
  for (int i = 0; i < n; i++)
  {
    a = v[i].fir, b = v[i].sec, ii = i;
    for (int k = 0; k < n; k++)
    {
      vis[k] = 0;
      mask[k] = 0;
    }
    dfs(a, 1);
    for (int k = 0; k < n; k++)
    {
      vis[k] = 0;
    }
    dfs(b, 2);
    for (int k = 0; k < n; k++)
    {
      vis[k] = 0;
    }
    dfs2(i, 4);
    bool ok = 0;
    for (int k = 0; k < n; k++)
    {
      if (mask[k] == 7)
        ok = 1;
    }
    (ok) ? cout << "Y" : cout << "N";
  }
  cout << endl;
}