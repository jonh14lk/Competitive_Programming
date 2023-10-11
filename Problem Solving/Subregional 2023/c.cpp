#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define MAXN 100005

int n;
vector<int> adj[MAXN];
int v[MAXN];
int ans[MAXN];
vector<int> q;
vector<pi> op;

void dfs(int s, int p)
{
  auto it = lower_bound(q.begin(), q.end(), v[s]);
  int pos = -1, prv;
  bool fl = 0;
  if (it == q.end())
  {
    q.pb(v[s]);
    pos = q.size() - 1;
    fl = 1;
  }
  else
  {
    pos = it - q.begin();
    prv = q[pos];
    q[pos] = v[s];
  }
  ans[s] = q.size();
  for (auto const &i : adj[s])
  {
    if (i == p)
      continue;
    dfs(i, s);
  }
  if (fl)
  {
    q.pop_back();
  }
  else
  {
    q[pos] = prv;
  }
}
signed main()
{
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int x;
    cin >> x;
    x--;
    adj[x].pb(i);
    adj[i].pb(x);
  }
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
  }
  dfs(0, -1);
  for (int i = 1; i < n; i++)
    cout << ans[i] << " ";
  cout << endl;
}