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
#define MAXN 10005
#define mod 998244353

struct edge
{
  int v, l, c;
};

pi dist[MAXN];
int par[MAXN];
bool vis[MAXN];
vector<edge> adj[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--;
    adj[a].pb({b, c, d});
    adj[b].pb({a, c, d});
  }
  for (int i = 0; i < n; i++)
  {
    dist[i] = {1e18, 1e18};
    par[i] = -1;
  }
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dist[0] = {0, 0};
  pq.push({dist[0], 0});
  while (!pq.empty())
  {
    pi c = pq.top().fir;
    int x = pq.top().sec;
    pq.pop();
    if (vis[x])
      continue;
    vis[x] = 1;
    for (auto const &i : adj[x])
    {
      pi new_c = {c.fir + i.l, i.c};
      if (dist[i.v] > new_c)
      {
        dist[i.v] = new_c;
        par[i.v] = x;
        pq.push({dist[i.v], i.v});
      }
    }
  }
  int ans = 0;
  for (int i = 1; i < n; i++)
    ans += dist[i].sec;
  cout << ans << endl;
  return 0;
}