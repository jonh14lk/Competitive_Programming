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

const int inf = 1e15;

struct color_upd
{
#define left fir
#define right sec.fir
#define color sec.sec
  set<pii> ranges;
  vector<pii> erased;

  color_upd(int n) // inicialmente, todo mundo pintado com a cor inf
  {
    // nao usar cores negativas!!!!!!!!!
    ranges.insert({0, {n - 1, inf}});
  }
  int get(int i) // qual a cor do elemento na posição i
  {
    auto it = ranges.upper_bound({i, {1e18, 1e18}});
    if (it == ranges.begin())
      return -1;
    it--;
    return (*(it)).color;
  }
  void del(int l, int r) // apaga o intervalo [l, r]
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
  void add(int a, int b, int c) // não ter dois intervalos adjacentes com a mesma cor no set de ranges
  {
    auto it = ranges.lower_bound({a, {b, 0}});
    pii aa = {-1, {-1, -1}};
    pii bb = {-1, {-1, -1}};
    if (it != ranges.end())
    {
      if ((*it).color == c && (*it).left == b + 1)
      {
        aa = *it;
        b = (*it).right;
      }
    }
    if (it != ranges.begin())
    {
      it--;
      if ((*it).color == c && (*it).right == a - 1)
      {
        bb = *it;
        a = (*it).left;
      }
    }
    ranges.erase(aa);
    ranges.erase(bb);
    ranges.insert({a, {b, c}});
  }
  void upd(int a, int b, int c) // pinta o intervalo [a, b] com a cor c
  {
    del(a, b);
    add(a, b, c);
  }
};
struct segtree
{
  vector<int> seg;
  vector<int> lazy;

  segtree(int n)
  {
    seg.resize(4 * n, 0);
    lazy.assign(4 * n, 0);
  }
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a + b;
  }
  void add(int i, int l, int r, int diff)
  {
    seg[i] += (r - l + 1) * diff;
    if (l != r)
    {
      lazy[i << 1] += diff;
      lazy[(i << 1) | 1] += diff;
    }
    lazy[i] = 0;
  }
  void update(int i, int l, int r, int ql, int qr, int diff)
  {
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(i, l, r, diff);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, diff);
    update((i << 1) | 1, mid + 1, r, ql, qr, diff);
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  color_upd c = color_upd(n);
  segtree s = segtree(n);
  for (int i = 0; i < n; i++)
    c.upd(i, i, i + 1);
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      c.upd(l, r, x);
      for (auto const &i : c.erased)
        s.update(1, 0, n - 1, i.left, i.right, abs(x - i.color));
    }
    else
    {
      int l, r;
      cin >> l >> r;
      l--, r--;
      cout << s.query(0, n - 1, l, r, 1) << endl;
    }
  }
  return 0;
}
// https://codeforces.com/contest/444/problem/C
