#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define double long double
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 502
#define MAXL 20
#define mod 998244353

int ans;
vector<int> adj[MAXN];
vector<pi> edges;
bool visited[MAXN];
int idade[MAXN];

void dfs(int s)
{
  visited[s] = true;
  for (auto const &i : adj[s])
    if (!visited[i])
      ans = min(ans, idade[i]), dfs(i);
}
signed main()
{
  int n, m, q;
  cin >> n >> m >> q;
  for (int i = 0; i < n; i++)
    cin >> idade[i];
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    edges.pb(mp(a, b));
    adj[b].pb(a);
  }
  while (q--)
  {
    char t;
    cin >> t;
    if (t == 'P')
    {
      int s;
      cin >> s;
      s--;
      memset(visited, false, sizeof(visited));
      ans = INT_MAX;
      dfs(s);
      (ans == INT_MAX) ? cout << "*\n" : cout << ans << endl;
    }
    else
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      for (int i = 0; i < n; i++)
        adj[i].clear();
      for (int i = 0; i < edges.size(); i++)
      {
        if (edges[i].fir == a)
          edges[i].fir = b;
        else if (edges[i].fir == b)
          edges[i].fir = a;
        if (edges[i].sec == a)
          edges[i].sec = b;
        else if (edges[i].sec == b)
          edges[i].sec = a;
        adj[edges[i].sec].pb(edges[i].fir);
      }
    }
  }
  return 0;
}