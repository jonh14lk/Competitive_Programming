#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007
#define PI acos(-1)

struct node
{
  int item, l, r;
  node() {}
  node(int l, int r, int item) : l(l), r(r), item(item) {}
};
int n, q;
vector<node> seg;
vector<int> roots;

void init()
{
  seg.resize(1);
}
int newleaf(int vv)
{
  int p = seg.size();
  seg.pb(node(0, 0, vv));
  return p;
}
int newpar(int l, int r)
{
  int p = seg.size();
  seg.pb(node(l, r, seg[l].item + seg[r].item));
  return p;
}
int upd(int i, int l, int r, int pos)
{
  if (l == r)
    return newleaf(seg[i].item + 1);
  int mid = (l + r) >> 1;
  if (pos <= mid)
    return newpar(upd(seg[i].l, l, mid, pos), seg[i].r);
  return newpar(seg[i].l, upd(seg[i].r, mid + 1, r, pos));
}
int build(int l, int r)
{
  if (l == r)
    return newleaf(0);
  int mid = (l + r) >> 1;
  return newpar(build(l, mid), build(mid + 1, r));
}
int qry(int vl, int vr, int l, int r, int k)
{
  if (l == r)
    return l;
  int mid = (l + r) >> 1;
  int c = seg[seg[vr].l].item - seg[seg[vl].l].item;
  if (c >= k)
    return qry(seg[vl].l, seg[vr].l, l, mid, k);
  return qry(seg[vl].r, seg[vr].r, mid + 1, r, k - c);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  vector<int> v(n);
  set<int> vals;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    vals.insert(v[i]);
  }
  int mx = 1;
  map<int, int> mp, mpr;
  for (auto const &i : vals)
  {
    mp[i] = mx;
    mpr[mx] = i;
    mx++;
  }
  init();
  roots.pb(build(0, mx));
  for (auto const &i : v)
    roots.pb(upd(roots.back(), 0, mx, mp[i]));
  while (q--)
  {
    char c;
    cin >> c;
    if (c == 'Q')
    {
      int l, r, k;
      cin >> l >> r >> k;
      l--, r--;
      cout << mpr[qry(roots[l], roots[r + 1], 0, mx, k)] << endl;
    }
    else
    {
      int x;
      cin >> x;
      x--;
      swap(v[x], v[x + 1]);
      int a = upd(roots[x], 0, mx, mp[v[x]]);
      int b = upd(a, 0, mx, mp[v[x + 1]]);
      roots[x + 1] = a, roots[x + 2] = b;
    }
  }
  return 0;
}
// https://neps.academy/br/exercise/127
// queries de k-esimo menor em um range
// e fazer um swap entre v[i] e v[i + 1]