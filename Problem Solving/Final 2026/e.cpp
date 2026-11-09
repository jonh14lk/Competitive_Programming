#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 500005
#define pi pair<int, int>
#define pb push_back
#define fir first
#define sec second
#define mod 998244353

int ans[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN];
vector<int> vec[MAXN];
int out[MAXN];

void dfs(int s)
{
  if (out[s] == 0)
  {
    vec[s].pb(s);
    return;
  }
  for (auto const &i : adj[s])
  {
    dfs(i);
    if (vec[i].size() > vec[s].size())
      swap(vec[i], vec[s]);
    for (auto j : vec[i])
      vec[s].pb(j);
    vec[i].clear();
  }
  if (vec[s].size() > 1)
  {
    ans[vec[s].back()] = s;
    vis[s] = 1;
    vec[s].pop_back();
  }
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int x;
    cin >> x;
    x--;
    adj[x].pb(i);
    out[x]++;
  }
  memset(ans, -1, sizeof(ans));
  dfs(0);
  if (vec[0].size() > 1 || vis[0])
  {
    cout << "*\n";
    return 0;
  }
  ans[vec[0].back()] = 0;
  for (int i = 0; i < n; i++)
  {
    cout << ans[i] + 1 << " ";
  }
  cout << endl;
}