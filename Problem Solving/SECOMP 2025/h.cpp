#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 500005

int n, m, timer;
string st;
vector<int> adj[MAXN];
int tin[MAXN];
int tout[MAXN];
int mask[MAXN];
vector<pair<int, int>> events_by_dep[MAXN];

void dfs(int s, int p, int dep)
{
  tin[s] = ++timer;
  mask[dep] ^= (1ll << (st[s] - 'a'));
  events_by_dep[dep].push_back({tin[s], mask[dep]});
  for (auto const &i : adj[s])
    dfs(i, s, dep + 1);
  tout[s] = timer;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 1; i < n; i++)
  {
    int p;
    cin >> p;
    p--;
    adj[p].push_back(i);
  }
  for (int d = 1; d <= n; d++)
  {
    events_by_dep[d].push_back({-1, 0});
  }
  cin >> st;
  timer = -1;
  dfs(0, -1, 1);
  while (m--)
  {
    int v, h;
    cin >> v >> h;
    v--;
    auto it = lower_bound(events_by_dep[h].begin(), events_by_dep[h].end(), make_pair(tout[v] + 1, -1));
    auto it2 = lower_bound(events_by_dep[h].begin(), events_by_dep[h].end(), make_pair(tin[v], -1));
    it--, it2--;
    int resp_mask = (*it).second ^ (*it2).second;
    (__builtin_popcount(resp_mask) <= 1) ? cout << "Yes\n" : cout << "No\n";
  }
  return 0;
}