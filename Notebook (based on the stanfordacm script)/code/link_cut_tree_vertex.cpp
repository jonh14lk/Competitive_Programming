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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

struct node
{
  int p, ch[2];
  int val, sub, lazy;
  bool rev;
  int sz;
  node() {}
  node(int v) : p(-1), val(v), sub(v), rev(0), sz(1), lazy(0)
  {
    ch[0] = ch[1] = -1;
  }
};
struct link_cut_tree
{
  vector<node> t;

  link_cut_tree()
  {
    t.clear();
  }
  static int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a ^ b;
  }
  void prop(int x)
  {
    if (t[x].lazy)
    {
      t[x].val = t[x].lazy;
      t[x].sub = t[x].val;
      if (t[x].ch[0] + 1)
        t[t[x].ch[0]].lazy = t[x].lazy;
      if (t[x].ch[1] + 1)
        t[t[x].ch[1]].lazy = t[x].lazy;
    }
    if (t[x].rev)
    {
      swap(t[x].ch[0], t[x].ch[1]);
      if (t[x].ch[0] + 1)
        t[t[x].ch[0]].rev ^= 1;
      if (t[x].ch[1] + 1)
        t[t[x].ch[1]].rev ^= 1;
    }
    t[x].lazy = 0, t[x].rev = 0;
  }
  void update(int x)
  {
    t[x].sz = 1, t[x].sub = t[x].val;
    for (int i = 0; i < 2; i++)
    {
      if (t[x].ch[i] + 1)
      {
        prop(t[x].ch[i]);
        t[x].sz += t[t[x].ch[i]].sz;
        t[x].sub = merge(t[x].sub, t[t[x].ch[i]].sub);
      }
    }
  }
  bool is_root(int x)
  {
    return t[x].p == -1 or (t[t[x].p].ch[0] != x and t[t[x].p].ch[1] != x);
  }
  void rotate(int x)
  {
    int p = t[x].p, pp = t[p].p;
    if (!is_root(p))
      t[pp].ch[t[pp].ch[1] == p] = x;
    bool d = t[p].ch[0] == x;
    t[p].ch[!d] = t[x].ch[d], t[x].ch[d] = p;
    if (t[p].ch[!d] + 1)
      t[t[p].ch[!d]].p = p;
    t[x].p = pp, t[p].p = x;
    update(p), update(x);
  }
  int splay(int x)
  {
    while (!is_root(x))
    {
      int p = t[x].p, pp = t[p].p;
      if (!is_root(p))
        prop(pp);
      prop(p), prop(x);
      if (!is_root(p))
        rotate((t[pp].ch[0] == p) ^ (t[p].ch[0] == x) ? x : p);
      rotate(x);
    }
    return prop(x), x;
  }
  int access(int v)
  {
    int last = -1;
    for (int w = v; w + 1; update(last = w), splay(v), w = t[v].p)
      splay(w), t[w].ch[1] = (last == -1 ? -1 : v);
    return last;
  }
  void make_tree(int v, int w = neutral()) // cria uma arvore com um unico vertice, sendo o vertice i
  {
    while (t.size() <= v)
      t.pb(node(neutral()));
    t[v] = node(w);
  }
  int find_root(int v) // acha a raiz da arvore do vertice v
  {
    access(v), prop(v);
    while (t[v].ch[0] + 1)
      v = t[v].ch[0], prop(v);
    return splay(v);
  }
  bool connected(int v, int w) // checa se v e w estao na mesma arvore (aka componente conexa)
  {
    access(v), access(w);
    return v == w ? true : t[v].p != -1;
  }
  void rootify(int v) // torna v a raiz de sua arvore
  {
    access(v);
    t[v].rev ^= 1;
  }
  int query(int v, int w) // query no caminho de v ate w
  {
    rootify(w), access(v);
    return t[v].sub;
  }
  void update(int v, int w, int x) // aplica o update em todos os vertices no caminho de v ate w
  {
    rootify(w), access(v);
    t[v].lazy = x;
  }
  void link(int v, int w) // adiciona a aresta v - w
  {
    rootify(w);
    t[w].p = v;
  }
  void cut(int v, int w) // remove a aresta v - w
  {
    rootify(w), access(v);
    t[v].ch[0] = t[t[v].ch[0]].p = -1;
  }
  int lca(int v, int w) // acha o lca(v, w)
  {
    access(v);
    return access(w);
  }
};

set<int> adj[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  int x = 0;
  link_cut_tree l;
  for (int i = 0; i < n; i++)
  {
    // l.make_tree(i, i) // poderia fazer isso tbm, para criar o vertice i com valor i
    l.make_tree(i);
    l.update(i, i, i); // testa o update
  }
  while (q--)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a = ((a * (1 + x)) % mod) % 2;
    b = ((b * (1 + x)) % mod) % n;
    c = ((c * (1 + x)) % mod) % n;
    if (a == 0)
    {
      adj[b].insert(c);
      adj[c].insert(b);
      l.link(b, c);
    }
    else
    {
      if (!l.connected(b, c))
      {
        x = 0;
        cout << x << endl;
        continue;
      }
      int d = l.query(b, c);
      d ^= b;
      d ^= c;
      x = 0;
      if (d >= 0 && d < n)
      {
        bool ok = 1;
        ok &= (adj[b].find(d) != adj[b].end());
        ok &= (adj[c].find(d) != adj[c].end());
        if (ok)
          x = d + 1;
      }
      cout << x << endl;
    }
  }
}
// problema exemplo: https://atcoder.jp/contests/abc350/tasks/abc350_g
// nesse caso, a link cut tree tem lazy para assign de valor
// e de queries de xor