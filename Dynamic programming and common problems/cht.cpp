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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 1000000007

struct line
{
  int m, b, p;
  line(int m, int b) : m(m), b(b) {}
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
  int ptr;
  vector<line> a;
  cht() { ptr = 0; }
  void add(line l)
  {
    while (1)
    {
      if (a.size() >= 1 && a.back().m == l.m && l.b > a.back().b)
      {
        a.pop_back();
      }
      else if (a.size() >= 1 && a.back().m == l.m && l.b <= a.back().b)
      {
        break;
      }
      else if (a.size() >= 2 && a.back().inter(l) >= a[a.size() - 2].inter(a.back()))
      {
        a.pop_back();
      }
      else
      {
        a.pb(l);
        break;
      }
    }
  }
  int get(int x)
  {
    if (!a.size())
      return -inf;
    while (ptr + 1 < a.size() && a[ptr].eval(x) <= a[ptr + 1].eval(x))
      ptr++;
    return a[ptr].eval(x);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// cht
// queries ordenadas em ordem decrescente
// linhas ordenadas em ordem decrescente
