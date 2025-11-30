#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

vector<int> adj[1005];
bool vis[1005];

void dfs(int s)
{
  vis[s] = 1;
  for (auto const &i : adj[s])
  {
    if (!vis[i])
      dfs(i);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  if (n % 2 == 0 && n > 2)
  {
    cout << "N\n";
    return 0;
  }
  set<pi> s;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
      s.insert({i, j});
  }
  int m;
  cin >> m;
  vector<int> v(m);
  for (int i = 0; i < m; i++)
  {
    cin >> v[i];
    v[i]--;
  }
  cin >> m;
  vector<int> v2(m);
  for (int i = 0; i < m; i++)
  {
    cin >> v2[i];
    v2[i]--;
  }
  auto get = [&](int i, int j)
  {
    if (i > j)
      swap(i, j);
    return pi(i, j);
  };
  auto check = [&](vector<int> &a)
  {
    for (int i = 1; i < a.size(); i++)
    {
      if (a[i] == a[i - 1])
        return 0;
      if (s.find(get(a[i - 1], a[i])) == s.end())
        return 0;
      s.erase(get(a[i - 1], a[i]));
    }
    return 1;
  };
  if (!check(v) || !check(v2))
  {
    cout << "N\n";
    return 0;
  }
  if (v.size() == 0 && v2.size() == 0)
  {
    cout << "Y\n";
    return 0;
  }
  if (n == 2)
  {
    if (v.size() < v2.size())
    {
      swap(v, v2);
    }
    if (v.size() == 2 && v2.size() == 0)
    {
      cout << "Y\n";
    }
    else if (v.size() == 1 && v2.size() == 1)
    {
      (v[0] != v2[0]) ? cout << "Y\n" : cout << "N\n";
    }
    else if (v.size() == 1 && v2.size() == 0)
    {
      cout << "Y\n";
    }
    else
    {
      cout << "N\n";
    }
    return 0;
  }
  else
  {
    if (v.size() > 0 && v2.size() > 0 && v.front() != v2.back())
    {
      cout << "N\n";
      return 0;
    }
  }
  if (s.size() == 0)
  {
    if (v.size() == 0 || v2.size() == 0)
      cout << "Y\n";
    else
      cout << "N\n";
    return 0;
  }
  for (auto [x, y] : s)
  {
    adj[x].pb(y);
    adj[y].pb(x);
  }
  if (v.size() == 0 && v2.size() > 0)
  {
    reverse(v2.begin(), v2.end());
    swap(v, v2);
  }
  int ini = v.back(), fim = (v2.size() == 0) ? -1 : v2.front();
  if (adj[ini].size() < 1)
  {
    cout << "N\n";
    return 0;
  }
  if (fim != -1 && adj[fim].size() < 1)
  {
    cout << "N\n";
    return 0;
  }
  int odd = 0;
  dfs(ini);
  for (int i = 0; i < n; i++)
  {
    if (adj[i].size() > 0 && !vis[i])
    {
      cout << "N\n";
      return 0;
    }
    odd += (adj[i].size() % 2);
  }
  if (odd != 0 && odd != 2)
  {
    cout << "N\n";
    return 0;
  }
  else if (odd == 0)
  {
    if (fim != -1 && ini != fim)
    {
      cout << "N\n";
      return 0;
    }
    if (adj[ini].size() < 2)
    {
      cout << "N\n";
      return 0;
    }
    cout << "Y\n";
  }
  else
  {
    if (adj[ini].size() % 2 == 0)
    {
      cout << "N\n";
      return 0;
    }
    if (fim != -1 && adj[fim].size() % 2 == 0)
    {
      cout << "N\n";
      return 0;
    }
    cout << "Y\n";
  }
  return 0;
}