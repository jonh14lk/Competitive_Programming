// https://codeforces.com/contest/863/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 101
 
vector<int> ans;
 
namespace treap
{
  struct treap
  {
    int data, priority;
    vector<treap *> kids;
    int subtree_size, sum, lazy;
  };
  int size(treap *node)
  {
    return (node == NULL) ? 0 : node->subtree_size;
  }
  void recalc(treap *node)
  {
    if (node == NULL)
      return;
    node->subtree_size = 1;
    node->sum = (node->data) + (node->lazy * size(node)); 
    for (auto const &i : node->kids)
    {
      if (i == NULL)
        continue;
      node->subtree_size += i->subtree_size;
      node->sum += ((i->sum) + (i->lazy * size(i)));
    }
  }
  void lazy_propagation(treap *node)
  {
    if (node == NULL || !(node->lazy))
      return;
    swap(node->kids[0], node->kids[1]);
    for (auto const &i : node->kids)
    {
      if (i == NULL)
        continue;
      i->lazy ^= 1;
    }
    node->lazy = 0;
  }
  vector<treap *> split(treap *node, int n)
  {
    if (node == NULL)
      return {NULL, NULL};
    lazy_propagation(node);
    if (size(node->kids[0]) >= n)
    {
      vector<treap *> left = split(node->kids[0], n);
      node->kids[0] = left[1];
      recalc(node);
      return {left[0], node};
    }
    else
    {
      vector<treap *> right = split(node->kids[1], n - size(node->kids[0]) - 1);
      node->kids[1] = right[0];
      recalc(node);
      return {node, right[1]};
    }
  }
  treap *merge(treap *l, treap *r)
  {
    if (l == NULL)
      return r;
    if (r == NULL)
      return l;
    lazy_propagation(l);
    lazy_propagation(r);
    if (l->priority < r->priority)
    {
      l->kids[1] = merge(l->kids[1], r);
      recalc(l);
      return l;
    }
    else
    {
      r->kids[0] = merge(l, r->kids[0]);
      recalc(r);
      return r;
    }
  }
  treap *create_node(int data, int priority)
  {
    treap *ret = new treap;
    ret->data = data;
    ret->priority = priority;
    ret->kids = {NULL, NULL};
    ret->subtree_size = 1;
    ret->sum = ret->data;
    ret->lazy = 0;
    return ret;
  }
  void dfs(treap *t)
  {
    if (t == NULL)
      return;
    lazy_propagation(t);
    dfs(t->kids[0]);
    ans.pb(t->data);
    dfs(t->kids[1]);
  }
  treap *shift(treap *t, int l, int r)
  {
    vector<treap *> a = split(t, l);
    vector<treap *> b = split(a[1], r - l + 1);
    vector<treap *> c = split(b[0], r - l);
    return merge(merge(a[0], c[1]), merge(c[0], b[1]));
  }
  treap *reverse(treap *t, int l, int r)
  {
    vector<treap *> a = split(t, l);
    vector<treap *> b = split(a[1], r - l + 1);
    b[0]->lazy ^= 1;
    return merge(a[0], merge(b[0], b[1]));
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  treap::treap *t = NULL;
  int n, m, q;
  cin >> n >> q >> m;
  for (int i = 0; i < n; i++)
  {
    int k;
    cin >> k;
    t = treap::merge(t, treap::create_node(k, rand()));
  }
  while (q--)
  {
    int ty, l, r;
    cin >> ty >> l >> r;
    l--, r--;
    (ty == 1) ? t = treap::shift(t, l, r) : t = treap::reverse(t, l, r);
  }
  treap::dfs(t);
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
