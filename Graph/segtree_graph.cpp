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
#define MAXN 500005
#define mod 998244353

struct segtree_graph
{
  int n;
  vector<vector<int>> adj;
  vector<int> id_rev, id, deg;

  segtree_graph(int sz)
  {
    n = sz;
    adj.resize(4 * n);
    id.resize(n);
    id_rev.assign(4 * n, -1);
    deg.assign(4 * n, 0);
    build(0, n - 1, 1);
  }
  void build(int l, int r, int i)
  {
    if (l == r)
    {
      id[l] = i;
      id_rev[i] = l;
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) | 1);
    adj[i << 1].pb(i);
    adj[(i << 1) | 1].pb(i);
    deg[i] += 2;
  }
  void add(int l, int r, int ql, int qr, int i, int x)
  {
    if (l > r || l > qr || r < ql)
    {
      return;
    }
    if (l >= ql && r <= qr)
    {
      adj[i].pb(x);
      deg[x]++;
      return;
    }
    int mid = (l + r) >> 1;
    add(l, mid, ql, qr, i << 1, x);
    add(mid + 1, r, ql, qr, (i << 1) | 1, x);
  }
  void add2(int a, int b)
  {
    adj[a].pb(b);
    deg[b]++;
  }
  void topological_sort()
  {
    vector<bool> vis(4 * n, 0);
    queue<int> q;
    for (int i = 0; i < (4 * n); i++)
    {
      if (!deg[i])
        q.push(i);
    }
    int qt = 0, xx = 1;
    vector<int> ans(n);
    while (!q.empty())
    {
      int x = q.front();
      q.pop();
      qt++;
      if (id_rev[x] != -1)
      {
        ans[id_rev[x]] = xx++;
      }
      for (auto const &i : adj[x])
      {
        deg[i]--;
        if (!deg[i])
          q.push(i);
      }
    }
    if (qt != (4 * n))
    {
      cout << "-1\n";
      return;
    }
    for (auto const &i : ans)
    {
      cout << i << " ";
    }
    cout << endl;
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
    int n;
    cin >> n;
    segtree_graph st(n);
    for (int i = 0; i < n; i++)
    {
      int x;
      cin >> x; // next[i]
      if (x != -1)
      {
        x--;
        if (x > (i + 1))
          st.add(0, n - 1, i + 1, x - 1, 1, st.id[i]);
        if (x < n)
          st.add2(st.id[i], st.id[x]);
      }
    }
    st.topological_sort();
  }
}
// https://codeforces.com/contest/1158/problem/C
// se next[i] = j
// entao p[j] > p[i]
// e para todo k tal que: i < k < j, p[k] < p[i]
// em outras palavras o primeiro caba a direita de i que eh maior do que p[i] eh no indice j
// montar o grafo de implicações e fazer topsort
// pq se next[i] = j
// entao implica que p[k] < p[i] para i < k < j
// e implica que p[i] < p[j]
// mas tem que ser o grafo de segtree ne

// faz algo similar ao problema legacy: https://codeforces.com/problemset/problem/786/B