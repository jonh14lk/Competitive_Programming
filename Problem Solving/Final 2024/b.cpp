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
#define MAXN 300006
#define mod 1000000007

int n, m;
vector<pi> adj[MAXN];
pi edges[MAXN];
int dep[MAXN];
bool vis[MAXN];
pi par[MAXN];
bool on_tree[MAXN];

void dfs(int s)
{
  vis[s] = 1;
  for (auto const &i : adj[s])
  {
    if (!vis[i.fir])
    {
      on_tree[i.sec] = 1;
      dep[i.fir] = dep[s] + 1;
      par[i.fir] = {s, i.sec};
      dfs(i.fir);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb({v, i});
    adj[v].pb({u, i});
    edges[i] = {u, v};
  }
  dfs(0);
  pi best = {-1, -1};
  for (int i = 0; i < m; i++)
  {
    auto [u, v] = edges[i];
    if (!on_tree[i])
      best = max(best, {min(dep[u], dep[v]), i});
  }
  auto [u, v] = edges[best.sec];
  if (dep[u] < dep[v])
    swap(u, v);
  vector<int> ans;
  // o caminho de u pra v eh sempre subindo, ja que [u, v] eh um backward edge
  while (u != v)
  {
    ans.pb(par[u].sec);
    u = par[u].fir;
  }
  ans.pb(best.sec);
  cout << ans.size() << endl;
  for (auto const &i : ans)
    cout << i + 1 << " ";
  cout << endl;
  return 0;
}