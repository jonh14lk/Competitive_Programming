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
#define MAXN 500001
#define mod 1000000007
#define left fir
#define right sec.fir
#define color sec.sec

struct color_upd
{
  set<pii> ranges;
  vector<pii> erased;
  vector<int> cnt;

  color_upd(int n, int c)
  {
    ranges.insert({0, {n - 1, 1}});
    cnt.assign(c + 1, 0);
    cnt[1] = n;
  }
  void del(int l, int r)
  {
    erased.clear();
    auto it = ranges.upper_bound({l, {0, 0}});
    if (it != ranges.begin())
    {
      it--;
    }
    while (it != ranges.end())
    {
      if ((*(it)).left > r)
        break;
      else if ((*(it)).right >= l)
        erased.push_back(*it);
      it++;
    }
    if (erased.size() > 0)
    {
      int sz = erased.size();
      auto it = ranges.lower_bound({erased[0].left, {0, 0}});
      auto it2 = ranges.lower_bound({erased[sz - 1].left, {0, 0}});
      pii ini = *it, fim = *it2;
      it2++;
      ranges.erase(it, it2);
      pii upd1 = {ini.left, {l - 1, ini.color}};
      pii upd2 = {r + 1, {fim.right, fim.color}};
      erased[0].left = max(erased[0].left, l);
      erased[sz - 1].right = min(erased[sz - 1].right, r);
      if (upd1.left <= upd1.right)
        ranges.insert(upd1);
      if (upd2.left <= upd2.right)
        ranges.insert(upd2);
    }
  }
  void upd(int a, int b, int c)
  {
    del(a, b);
    for (auto const &i : erased)
    {
      int sz = i.right - i.left + 1;
      cnt[i.color] -= sz;
      cnt[c] += sz;
    }
    ranges.insert({a, {b, c}});
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int l, colors, n;
  cin >> l >> colors >> n;
  color_upd c(l, colors);
  while (n--)
  {
    int p, x, a, b;
    cin >> p >> x >> a >> b;
    int s = c.cnt[p];
    int m1 = (a + (s * s)) % l;
    int m2 = (a + ((s + b) * (s + b))) % l;
    if (m1 > m2)
      swap(m1, m2);
    c.upd(m1, m2, x);
  }
  int ans = 0;
  for (int i = 1; i <= colors; i++)
  {
    if (c.cnt[i] > c.cnt[ans])
      ans = i;
  }
  cout << c.cnt[ans] << endl;
  return 0;
}
