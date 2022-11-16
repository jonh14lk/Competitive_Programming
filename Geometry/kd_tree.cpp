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
#define MAXN 300005
#define mod 998244353
#define inf LLONG_MAX

struct pt
{
  int x, y, id;
  pt() {}
  pt(int xx, int yy) { x = xx, y = yy; }
  pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
  bool operator<(pt p) const { return x < p.x; }
  int dist() const { return x * x + y * y; }
};
bool on_x(const pt &a, const pt &b) { return a.x < b.x; }
bool on_y(const pt &a, const pt &b) { return a.y < b.y; }
struct node
{
  pt pp;
  int id;
  int x0 = inf, x1 = -inf, y0 = inf, y1 = -inf;
  node *first = 0, *second = 0;
  int distance(const pt &p)
  {
    int x = (p.x < x0 ? x0 : p.x > x1 ? x1
                                      : p.x);
    int y = (p.y < y0 ? y0 : p.y > y1 ? y1
                                      : p.y);
    return (pt(x, y) - p).dist();
  }
  node(vector<pt> &&vp) : pp(vp[0])
  {
    for (pt p : vp)
    {
      x0 = min(x0, p.x);
      x1 = max(x1, p.x);
      y0 = min(y0, p.y);
      y1 = max(y1, p.y);
    }
    if (vp.size() > 1)
    {
      sort(vp.begin(), vp.end(), x1 - x0 >= y1 - y0 ? on_x : on_y);
      int half = vp.size() / 2;
      first = new node({vp.begin(), vp.begin() + half});
      second = new node({vp.begin() + half, vp.end()});
    }
  }
};
struct kd_tree
{
  node *root;
  kd_tree(const vector<pt> &vp) : root(new node({vp.begin(), vp.end()})) {}
  pi search(node *n, const pt &p)
  {
    if (!n->first)
    {
      if (n->pp.x == p.x && n->pp.y == p.y)
        return make_pair(inf, n->pp.id); // distancia infinita pra pontos iguais
      return make_pair((p - n->pp).dist(), n->pp.id);
    }
    node *f = n->first, *s = n->second;
    int bfirst = f->distance(p), bsec = s->distance(p);
    if (bfirst > bsec)
      swap(bsec, bfirst), swap(f, s);
    auto best = search(f, p);
    if (bsec < best.first || (!f->first))
      best = min(best, search(s, p));
    return best;
  }
  pi nearest(const pt &p)
  {
    return search(root, p);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pt> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x >> v[i].y;
    v[i].id = i;
  }
  kd_tree t(v);
  pii ans = {inf, {inf, inf}};
  for (int i = 0; i < n; i++)
  {
    pi curr = t.nearest(v[i]);
    ans = min(ans, {curr.fir, {i, curr.sec}});
  }
  cout << fixed << setprecision(6) << ans.sec.fir << " " << ans.sec.sec << " " << sqrt(ans.fir) << endl;
  return 0;
}
// closest pair of points com kdtree
// da pra ser adaptado pro 3d tbm
// quando um ponto (x, y) pode aparecer em mais de um indice, tratar antes
// fonte: https://github.com/kth-competitive-programming/kactl/blob/main/kactl.pdf

// testei em:
// https://codeforces.com/contest/429/problem/D
// https://www.spoj.com/problems/CLOPPAIR/
// https://vjudge.net/problem/UVA-10245
// https://codeforces.com/gym/104020/problem/L (3D)
