#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define pi pair<int, int>
#define ps pair<double, string>
#define pib pair<pi, bool>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 5201
#define mod 1000000007

int n, k, at;
vector<int> adj[MAXN];
vector<int> adj2[MAXN];
vector<int> leafs;
vector<int> kappa;
bool visited[MAXN];
int prof[MAXN];

bool cmp(int a, int b)
{
  return prof[a] > prof[b];
}
void dfs(int s)
{
  visited[s] = true;
  if (adj[s].size() == 0)
    leafs.pb(s);
  else
    for (int i = 0; i < adj[s].size(); i++)
      if (!visited[adj[s][i]])
        prof[adj[s][i]] = prof[s] + 1, dfs(adj[s][i]);
}
void dfs2(int s)
{
  visited[s] = true;
  at++;
  if (s == 1)
    return;
  if (!visited[adj2[s][0]])
    dfs2(adj2[s][0]);
}
signed main()
{
  cin >> n >> k;
  for (int i = 2; i <= n; i++)
  {
    int a;
    cin >> a;
    adj[a].pb(i);
    adj2[i].pb(a);
  }
  prof[1] = 0;
  dfs(1);
  sort(leafs.begin(), leafs.end(), cmp);
  memset(visited, false, sizeof(visited));
  for (auto const &i : leafs)
  {
    at = 0;
    dfs2(i);
    kappa.pb(at);
  }
  int ans = 0;
  sort(kappa.rbegin(), kappa.rend());
  for (int i = 0; i < min(k, int(kappa.size())); i++)
    ans += kappa[i];
  cout << ans << endl;
  return 0;
}