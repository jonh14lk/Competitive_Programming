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
#define MAXN 1000005
#define mod 1000000007

struct treap
{
  int data, priority;
  int sz, lazy2;
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
  if (node == NULL)
    return;
  if (node->lazy2)
  {
    if (node->l)
      node->l->lazy2 += node->lazy2;
    if (node->r)
      node->r->lazy2 += node->lazy2;
    node->data += node->lazy2;
    node->lazy2 = 0;
  }
  if (node->lazy)
  {
    swap(node->l, node->r);
    if (node->l)
      node->l->lazy = !node->l->lazy;
    if (node->r)
      node->r->lazy = !node->r->lazy;
    node->lazy = 0;
  }
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
void troca(treap *&t, int l, int r, int ll, int rr)
{
  treap *a0, *a1, *b0, *b1, *c0, *c1, *d0, *d1;
  split(t, a0, a1, l);
  split(a1, b0, b1, r - l + 1);
  ll -= (r + 1);
  rr -= (r + 1);
  split(b1, c0, c1, ll);
  split(c1, d0, d1, rr - ll + 1);
  merge(t, a0, d0);
  merge(t, t, c0);
  merge(t, t, b0);
  merge(t, t, d1);
}
void add(treap *&t, int l, int r)
{
  treap *a0, *a1, *b0, *b1;
  split(t, a0, a1, l);
  split(a1, b0, b1, r - l + 1);
  b0->lazy ^= 1;
  b0->lazy2 += 1;
  merge(t, a0, b0);
  merge(t, t, b1);
}
void solve(int x)
{
  x = x % 26;
  char c = x + 'a';
  cout << c;
}
void dfs(treap *t)
{
  if (!t)
    return;
  lazy_propagation(t);
  dfs(t->l);
  solve(t->data);
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
  ret->lazy2 = 0;
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  int q;
  cin >> q;
  while (q--)
  {
    int n, m;
    string s;
    cin >> s >> m;
    n = s.size();
    treap *t = 0;
    for (auto const &i : s)
    {
      int x = i - 'a';
      merge(t, t, create_node(x, rand()));
    }
    while (m--)
    {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      a--, b--, c--, d--;
      add(t, a, b);
      add(t, c, d);
      troca(t, a, b, c, d);
    }
    dfs(t);
    cout << endl;
  }
  return 0;
}
// https://vjudge.net/contest/478186#problem/E
// - lazy propagation
// - reverse range with lazy propagation
// - swap ranges with equal lenght