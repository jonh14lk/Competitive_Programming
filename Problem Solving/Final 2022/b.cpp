#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1005
#define mod 1000000007

struct line
{
  mutable int m, b, p;
  bool operator<(const line &o) const
  {
    if (m != o.m)
      return m < o.m;
    return b < o.b;
  }
  bool operator<(const int x) const { return p < x; }
  int eval(int x) const { return m * x + b; }
  int inter(const line &o) const
  {
    int x = b - o.b, y = o.m - m;
    return (x / y) - ((x ^ y) < 0 && x % y);
  }
};
struct cht
{
  int INF = 1e18;
  multiset<line, less<>> l;
  void add(int m, int b)
  {
    auto y = l.insert({m, b, INF});
    auto z = next(y);
    if (z != l.end() && y->m == z->m)
    {
      l.erase(y);
      return;
    }
    if (y != l.begin())
    {
      auto x = prev(y);
      if (x->m == y->m)
        x = l.erase(x);
    }
    while (1)
    {
      if (z == l.end())
      {
        y->p = INF;
        break;
      }
      y->p = y->inter(*z);
      if (y->p < z->p)
        break;
      else
        z = l.erase(z);
    }
    if (y == l.begin())
      return;
    z = y;
    auto x = --y;
    while (1)
    {
      int ninter = x->inter(*z);
      if (ninter <= x->p)
        x->p = ninter;
      else
      {
        l.erase(z);
        break;
      }
      if (x == l.begin())
        break;
      y = x;
      x--;
      if (x->p < y->p)
        break;
      else
        l.erase(y);
    }
  }
  int get(int x)
  {
    if (l.empty())
      return 0;
    return l.lower_bound(x)->eval(x);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
  }
  int q;
  cin >> q;
  vector<pi> qry(q);
  for (int i = 0; i < q; i++)
  {
    cin >> qry[i].fir >> qry[i].sec;
  }
  vector<int> l(n);
  vector<int> r(n);
  vector<vector<int>> on(q);
  for (int i = 0; i < n; i++)
  {
    l[i] = 0;
    r[i] = q;
  }
  while (1)
  {
    bool ok = 1;
    for (int i = 0; i < n; i++)
    {
      if (l[i] < r[i])
      {
        ok = 0;
        int mid = (l[i] + r[i]) >> 1;
        on[mid].pb(i);
      }
    }
    if (ok)
    {
      break;
    }
    cht c;
    for (int mid = 0; mid < q; mid++)
    {
      c.add(qry[mid].fir, qry[mid].sec);
      for (auto const &j : on[mid])
      {
        (c.get(v[j].fir) > v[j].sec) ? r[j] = mid : l[j] = mid + 1;
      }
      on[mid].clear();
    }
  }
  vector<vector<int>> ans(q + 1);
  for (int i = 0; i < n; i++)
    ans[l[i]].pb(i + 1);
  for (int i = 0; i < q; i++)
  {
    cout << ans[i].size() << " ";
    for (auto const &j : ans[i])
      cout << j << " ";
    cout << endl;
  }
}
// busca binaria paralela pra saber o momento em que o ponto (x, y) vai ser removido