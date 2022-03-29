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

vector<int> ans;

struct treap
{
  int data, priority;
  int sz;
  bool lazy;
  treap *l, *r;
};
int size(treap *node)
{
  return (!node) ? 0 : node->sz;
}
void recalc(treap *node)
{
  if (!node)
    return;
  node->sz = 1;
  if (node->l)
    node->sz += node->l->sz;
  if (node->r)
    node->sz += node->r->sz;
}
void lazy_propagation(treap *node)
{
  if (!node || !(node->lazy))
    return;
  swap(node->l, node->r);
  if (node->l)
    node->l->lazy ^= 1;
  if (node->r)
    node->r->lazy ^= 1;
  node->lazy = 0;
}
void merge(treap *&t, treap *l, treap *r)
{
  lazy_propagation(l);
  lazy_propagation(r);
  if (!l)
    t = r;
  else if (!r)
    t = l;
  else if (l->priority > r->priority)
    merge(l->r, l->r, r), t = l;
  else
    merge(r->l, l, r->l), t = r;
  recalc(t);
}
void split(treap *t, treap *&l, treap *&r, int n)
{
  if (!t)
    return void(l = r = 0);
  lazy_propagation(t);
  if (size(t->l) >= n)
    split(t->l, l, t->l, n), r = t;
  else
    split(t->r, t->r, r, n - size(t->l) - 1), l = t;
  recalc(t);
}
void reverse(treap *&t, int l, int r)
{
  treap *a0, *a1, *b0, *b1;
  split(t, a0, a1, l);
  split(a1, b0, b1, r - l + 1);
  b0->lazy ^= 1;
  merge(t, a0, b0);
  merge(t, t, b1);
}
void shift(treap *&t, int l, int r)
{
  treap *a0, *a1, *b0, *b1, *c0, *c1;
  split(t, a0, a1, l);
  split(a1, b0, b1, r - l + 1);
  split(b0, c0, c1, r - l);
  merge(t, a0, c1);
  merge(t, t, c0);
  merge(t, t, b1);
}
void dfs(treap *t)
{
  if (!t)
    return;
  lazy_propagation(t);
  dfs(t->l);
  ans.pb(t->data);
  dfs(t->r);
}
treap *create_node(int data, int priority)
{
  treap *ret = new treap;
  ret->data = data;
  ret->priority = priority;
  ret->l = 0;
  ret->r = 0;
  ret->sz = 1;
  ret->lazy = 0;
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  treap *t = 0;
  int n, m, q;
  cin >> n >> q >> m;
  for (int i = 0; i < n; i++)
  {
    int k;
    cin >> k;
    merge(t, t, create_node(k, rand()));
  }
  while (q--)
  {
    int ty, l, r;
    cin >> ty >> l >> r;
    l--, r--;
    (ty == 1) ? shift(t, l, r) : reverse(t, l, r);
  }
  dfs(t);
  while (m--)
  {
    int i;
    cin >> i;
    i--;
    cout << ans[i] << " ";
  }
  cout << endl;
  return 0;
}