#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second
#define pb push_back
#define PI acos(-1)
#define MAXN 100005

pi qry[MAXN];
vector<pi> adj[MAXN];
vector<int> qries[MAXN];
set<pi> claim[MAXN];
int ans[MAXN];
int cnt[MAXN];

void dfs(int s, int p)
{
  if (adj[s].size() == 1)
  {
    claim[s].insert({0, s});
  }
  for (auto const &j : adj[s])
  {
    if (j.fir != p)
    {
      dfs(j.fir, s);
      pi win = *claim[j.fir].begin();
      pi ot = {win.fir + j.sec, win.sec};
      claim[s].insert(ot);
    }
  }
  pi win = *claim[s].begin();
  cnt[win.sec]++;
}
void dfs2(int s, int p)
{
  for (auto const &j : qries[s])
  {
    ans[j] = cnt[qry[j].fir];
  }
  for (auto const &j : adj[s])
  {
    if (j.fir != p)
    {
      pi win = *claim[j.fir].begin();
      pi ot = {win.fir + j.sec, win.sec};
      cnt[(*claim[s].begin()).sec]--;
      claim[s].erase(ot);
      cnt[(*claim[s].begin()).sec]++;

      pi win2 = *claim[s].begin();
      pi ot2 = {win2.fir + j.sec, win2.sec};
      cnt[(*claim[j.fir].begin()).sec]--;
      claim[j.fir].insert(ot2);
      cnt[(*claim[j.fir].begin()).sec]++;

      dfs2(j.fir, s);

      cnt[(*claim[j.fir].begin()).sec]--;
      claim[j.fir].erase(ot2);
      cnt[(*claim[j.fir].begin()).sec]++;

      cnt[(*claim[s].begin()).sec]--;
      claim[s].insert(ot);
      cnt[(*claim[s].begin()).sec]++;
    }
  }
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    adj[b].pb({a, c});
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int s, t;
    cin >> s >> t;
    s--, t--;
    qry[i] = {s, t};
    qries[t].pb(i);
  }
  dfs(0, -1);
  dfs2(0, -1);
  for (int i = 0; i < q; i++)
    cout << ans[i] << endl;
}