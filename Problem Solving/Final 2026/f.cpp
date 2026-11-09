#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

vector<int> adj[MAXN];
int v[MAXN];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  int ans = 0;
  set<pi> s;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    v[i] = x;
    s.insert({i, v[i]});
    adj[v[i]].pb(i);
    if (i >= 1)
      ans += (v[i] != v[i - 1]);
  }
  int sum = ans;
  auto rem = [&](int i)
  {
    auto it = s.find({i, v[i]});
    auto nxt = it;
    auto prv = it;
    nxt++;
    bool has_prv = 0, has_nxt = 0;
    if (nxt != s.end())
    {
      has_nxt = 1;
      if (v[i] != (*nxt).sec)
        sum--;
    }
    if (it != s.begin())
    {
      has_prv = 1;
      prv--;
      if (v[i] != (*prv).sec)
        sum--;
    }
    if (has_prv && has_nxt)
    {
      if ((*nxt).sec != (*prv).sec)
        sum++;
    }
    s.erase(*it);
  };
  auto add = [&](int i)
  {
    s.insert({i, v[i]});
    auto it = s.find({i, v[i]});
    auto nxt = it;
    auto prv = it;
    nxt++;
    bool has_prv = 0, has_nxt = 0;
    if (nxt != s.end())
    {
      has_nxt = 1;
      if (v[i] != (*nxt).sec)
        sum++;
    }
    if (it != s.begin())
    {
      has_prv = 1;
      prv--;
      if (v[i] != (*prv).sec)
        sum++;
    }
    if (has_prv && has_nxt)
    {
      if ((*nxt).sec != (*prv).sec)
        sum--;
    }
  };
  for (int i = 1; i <= n; i++)
  {
    for (auto const &j : adj[i])
      rem(j);
    ans = min(ans, sum);
    for (auto const &j : adj[i])
      add(j);
  }
  cout << ans << endl;
}
