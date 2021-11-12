#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007
#define PI acos(-1)

const double EPS = 1e-9;

struct pt
{
  int x, y;
};
struct seg
{
  pt p, q;
  int id;
  double get_y(int x) const
  {
    if (p.x == q.x)
      return p.y;
    return p.y + (q.y - p.y) * 1.0 * (x - p.x) / (q.x - p.x);
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
pi get_nxt(seg l)
{
  if (l.p.y == l.q.y)
    return {-1, l.q.y};
  if (l.p.y > l.q.y)
    return {l.p.x, l.p.y};
  return {l.q.x, l.q.y};
}
bool operator<(const seg &a, const seg &b)
{
  int x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
  return a.get_y(x) < b.get_y(x) - EPS;
}
struct event
{
  int x;
  int tp, id;
  event() {}
  event(int x, int tp, int id) : x(x), tp(tp), id(id) {}
  bool operator<(const event &e) const
  {
    if (abs(x - e.x) > EPS)
      return x < e.x;
    return tp < e.tp;
  }
};

set<seg> s;
vector<set<seg>::iterator> where;

set<seg>::iterator prev(set<seg>::iterator it)
{
  return it == s.begin() ? s.end() : --it;
}
set<seg>::iterator next(set<seg>::iterator it)
{
  return ++it;
}
void line_sweep(vector<seg> &v, vector<int> &queries)
{
  vector<event> e;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i].p.y > v[i].q.y)
      swap(v[i].p, v[i].q);
    e.pb({min(v[i].p.x, v[i].q.x), 0, i});
    e.pb({max(v[i].p.x, v[i].q.x), 2, i});
    e.pb({v[i].q.x, 1, i});
  }
  for (auto const &i : queries)
  {
    e.pb({i, 1, -1});
  }
  sort(e.begin(), e.end());
  where.resize(v.size());
  for (int i = 0; i < e.size(); i++)
  {
    int id = e[i].id;
    if (e[i].tp == 0)
    {
      auto nxt = s.lower_bound(v[id]);
      where[id] = s.insert(nxt, v[id]);
    }
    else if (e[i].tp == 2)
    {
      s.erase(where[id]);
    }
    else
    {
      int x = e[i].x;
      int y = (id == -1) ? 0 : v[id].get_y(x);
      auto it = (id == -1) ? s.begin() : where[id];
      while (it != s.end())
      {
        seg curr = *it;
        if (curr.id == id)
          it++;
        else
          break;
      }
      if (it != s.end())
      {
        int nxt_id = (*it).id;
        nxt[{x, y}] = get_nxt(v[nxt_id]);
      }
      else
      {
        nxt[{x, y}] = {-1, -1};
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<seg> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].p.x >> v[i].p.y >> v[i].q.x >> v[i].q.y;
    v[i].id = i;
  }
  vector<int> queries(q);
  for (int i = 0; i < q; i++)
    cin >> queries[i];
  line_sweep(v, queries);
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