#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct node
{
  int p, ch[2];
  pii val, sub;
  bool rev;
  int sz, ar;
  int lazy;
  node() {}
  node(pii v, int ar_) : p(-1), val(v), sub(v), rev(0), sz(ar_), ar(ar_), lazy(0)
  {
    ch[0] = ch[1] = -1;
  }
};
struct link_cut_tree
{
  vector<node> t;
  map<pair<int, int>, int> aresta;
  int sz, n;

  link_cut_tree(int nn)
  {
    t.clear();
    n = nn;
    sz = 0;
  }
  static pii neutral()
  {
    return {0, {0, 0}};
  }
  pii merge(pii a, pii b)
  {
    return max(a, b);
  }
  void prop(int x)
  {
    if (t[x].lazy)
    {
      if (t[x].ar)
        t[x].val.fir = t[x].lazy;
      t[x].sub = merge(t[x].sub, t[x].val);
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
    t[x].sz = t[x].ar, t[x].sub = t[x].val;
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
  void make_tree(int v, pii w = neutral(), int ar = 0)
  {
    while (t.size() <= v)
      t.pb(node(neutral(), 0));
    t[v] = node(w, ar);
  }
  int find_root(int v)
  {
    access(v), prop(v);
    while (t[v].ch[0] + 1)
      v = t[v].ch[0], prop(v);
    return splay(v);
  }
  bool conn(int v, int w)
  {
    access(v), access(w);
    return v == w ? true : t[v].p != -1;
  }
  void rootify(int v)
  {
    access(v);
    t[v].rev ^= 1;
  }
  pii query(int v, int w)
  {
    rootify(w), access(v);
    return t[v].sub;
  }
  void update(int v, int w, int x)
  {
    rootify(w), access(v);
    t[v].lazy += x;
  }
  void link_(int v, int w)
  {
    rootify(w);
    t[w].p = v;
  }
  void link(int v, int w, pii x)
  {
    int id = n + sz++;
    aresta[make_pair(v, w)] = id;
    make_tree(id, x, 1);
    link_(v, id), link_(id, w);
  }
  void cut_(int v, int w)
  {
    rootify(w), access(v);
    t[v].ch[0] = t[t[v].ch[0]].p = -1;
  }
  void cut(int v, int w)
  {
    int id = aresta[make_pair(v, w)];
    cut_(v, id), cut_(id, w);
  }
  int lca(int v, int w)
  {
    access(v);
    return access(w);
  }
};
struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  void make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      tot--;
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n, m, qq;
    cin >> n >> m >> qq;
    vector<pii> e;
    for (int i = 0; i < m; i++)
    {
      int a, b, c;
      cin >> a >> b >> c;
      a--, b--;
      e.pb({c, {a, b}});
    }
    sort(e.begin(), e.end());
    dsu d(n);
    link_cut_tree l(n);
    for (int i = 0; i < n; i++)
    {
      l.make_tree(i);
    }
    int cost = 0;
    for (auto const &i : e)
    {
      if (d.find_set(i.sec.fir) != d.find_set(i.sec.sec))
      {
        d.make_set(i.sec.fir, i.sec.sec);
        l.link(i.sec.fir, i.sec.sec, i);
        cost += i.fir;
      }
    }
    while (qq--)
    {
      int a, b, c;
      cin >> a >> b >> c;
      a--, b--;
      pii mx = l.query(a, b);
      if (c < mx.fir)
      {
        cost -= mx.fir;
        cost += c;
        l.cut(mx.sec.fir, mx.sec.sec);
        // l.link(a, b, {c, {a, b}}); poderia fazer assim, mas quero testar o update
        l.link(a, b, {0, {a, b}});
        l.update(a, b, c);
      }
      cout << cost << endl;
    }
  }
  return 0;
}
// link cut tree com peso nas arestas
// solução para o: https://codeforces.com/gym/101047/problem/I
// problema onde é dado um grafo inicial e algumas queries
// cada query adiciona uma nova aresta nesse grafo
// e o objetivo é achar a mst apos cada adição de aresta

// implementação baseada na: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lctAresta.cpp

// make_tree(v) cria uma nova arvore com um um único vertice
// rootify(v) torna v a raiz de sua arvore
// cut(u, v) apaga a aresta u, v
// link(u, v, c) adiciona a aresta de u até v com peso c
// query(v, w) retorna a aresta de maior peso no caminho de v até w
// update(v, w, x) faz com que as arestas do caminho de v até w passem a ter peso x
// operações tem complexidade O(log(n)) amortizado