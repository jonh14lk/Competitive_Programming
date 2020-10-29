#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 5001

struct treap // struct
{
  int data, priority;
  vector<treap *> kids;
  int subtree_size, sum, lazy;
};
int size(treap *node) // retorna o tamanho da subtree do no
{
  return (node == NULL) ? 0 : node->subtree_size;
}
void recalc(treap *node) // recalculo das informacoes do no
{
  if (node == NULL)
    return;
  node->subtree_size = 1;
  node->sum = (node->data) + (node->lazy * size(node)); // lazy propagation
  for (auto const &i : node->kids)
  {
    if (i == NULL)
      continue;
    node->subtree_size += i->subtree_size;
    node->sum += ((i->sum) + (i->lazy * size(i)));
  }
}
void lazy_propagation(treap *node) // para aplicar o lazy
{
  if (node == NULL || !(node->lazy))
    return;
  for (auto const &i : node->kids)
  {
    if (i == NULL)
      continue;
    i->lazy += node->lazy;
  }
  node->data += node->lazy;
  node->lazy = 0;
}
vector<treap *> split(treap *node, int n) // n = quantidade de elementos na subarvore da esquerda
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
treap *merge(treap *l, treap *r) // merge entre duas treaps
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
treap *add(treap *t, int l, int r, int k) // add pro lazy propagation
{
  vector<treap *> a = split(t, l);
  vector<treap *> b = split(a[1], r - l + 1);
  b[0]->lazy += k;
  return merge(a[0], merge(b[0], b[1]));
}
treap *create_node(int data, int priority) // criar um novo no
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
void print_treap(treap *t) // dfs in treap tree
{
  if (t == NULL)
    return;
  lazy_propagation(t);
  print_treap(t->kids[0]);
  cout << t->data << " ";
  print_treap(t->kids[1]);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL)); // para as prioridades
  treap *t = NULL;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int k;
    cin >> k;
    t = merge(t, create_node(k, rand()));
  }
  print_treap(t);
  cout << endl;
  int q;
  cin >> q;
  while (q--)
  {
    int l, r, k; // test lazy propagation
    cin >> l >> r >> k;
    t = add(t, l, r, k);
    print_treap(t);
    cout << endl;
  }
  return 0;
}
