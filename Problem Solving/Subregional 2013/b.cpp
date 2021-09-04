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
#define MAXN 2000
#define mod 1000000

struct line
{
  int a, b, c, d;
};
struct event
{
  int type, idx, x, y;
  bool operator<(const event ot)
  {
    if (x != ot.x)
      return x < ot.x;
    return type < ot.type;
  }
};

map<pi, pi> nxt;
map<pi, pi> dp;
map<pi, bool> vis;

pi solve(pi i)
{
  if (vis[i])
    return dp[i];
  if (nxt[i].fir == -1 && nxt[i].sec == -1)
    return dp[i] = {i.fir, -1};
  if (nxt[i].fir == -1)
    return dp[i] = {i.fir, nxt[i].sec};
  vis[i] = true;
  return dp[i] = solve(nxt[i]);
}
pi get_nxt(line l)
{
  if (l.b == l.d)
    return {-1, l.d};
  if (l.b > l.d)
    return {l.a, l.b};
  return {l.c, l.d};
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<line> v;
  vector<bool> can_finish;
  vector<event> e;
  for (int i = 0; i < n; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a > c)
    {
      swap(a, c);
      swap(b, d);
    }
    v.pb({a, b, c, d});
    e.pb({0, i, a, max(d, b)});
    e.pb({1, i, c + 1, max(d, b)});
    if (b > d)
      e.pb({2, i, a, b});
    else if (d > b)
      e.pb({2, i, c, d});
  }
  vector<int> queries(q);
  for (int i = 0; i < q; i++)
  {
    cin >> queries[i];
    e.pb({2, -1, queries[i], 0});
  }
  sort(e.begin(), e.end());
  set<pi> lines;
  for (auto const &i : e)
  {
    int type = i.type, idx = i.idx, x = i.x, y = i.y;
    if (type == 0)
    {
      lines.insert({y, idx});
    }
    else if (type == 1)
    {
      lines.erase({y, idx});
    }
    else
    {
      auto it = lines.lower_bound({y, -1});
      while (it != lines.end())
      {
        pi curr = *it;
        if (curr.sec == idx)
          it++;
        else
          break;
      }
      if (it != lines.end())
      {
        pi curr = *it;
        nxt[{x, y}] = get_nxt(v[curr.sec]);
      }
      else
      {
        nxt[{x, y}] = {-1, -1};
      }
    }
  }
  for (auto const &i : queries)
  {
    pi ans = solve({i, 0});
    if (ans.sec == -1)
      cout << ans.fir << endl;
    else
      cout << ans.fir << " " << ans.sec << endl;
  }
  return 0;
}