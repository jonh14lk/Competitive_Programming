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
#define MAXN 100005

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

int n, m;
vector<pi> edges;
vector<int> g[MAXN];
vector<int> t[MAXN];
set<int> adj[MAXN];

// https://github.com/ShahjalalShohag/code-library/blob/main/Graph%20Theory/Chordal%20Graph.cpp
// 1-indexed
vector<int> PEO() // O(n + m)
{
  int top = 0;
  vector<int> ord, vis(n + 1, 0), indeg(n + 1, 0);
  vector<vector<int>> bucket(n); // bucket dijkstra
  for (int i = 1; i <= n; ++i)
    bucket[0].push_back(i);
  for (int i = 1; i <= n;)
  {
    while (bucket[top].empty())
      --top;
    int u = bucket[top].back();
    bucket[top].pop_back();
    if (vis[u])
      continue;
    ord.push_back(u);
    vis[u] = 1;
    ++i;
    for (int v : g[u])
    {
      if (vis[v])
        continue;
      bucket[++indeg[v]].push_back(v);
      top = max(top, indeg[v]);
    }
  }
  reverse(ord.begin(), ord.end());
  return ord;
}
bool is_chordal(vector<int> &ord)
{
  vector<int> pos(n + 1);
  for (int i = 0; i < n; i++)
  {
    pos[ord[i]] = i;
  }
  for (int u = 1; u <= n; u++)
  {
    int mn = n + 1;
    for (auto v : g[u])
    {
      if (pos[u] < pos[v])
        mn = min(mn, pos[v]);
    }
    if (mn != n + 1)
    {
      int p = ord[mn];
      for (auto v : g[u])
      {
        if (pos[v] > pos[u] && v != p && !binary_search(edges.begin(), edges.end(), pi(min(v, p), max(v, p))))
          return 0;
      }
    }
  }
  return 1;
}
bool check(vector<pi> &ans)
{
  dsu d(n + 1);
  for (int i = 0; i <= n; i++)
  {
    t[i].clear();
  }
  for (int i = 0; i < ans.size(); i++)
  {
    if (ans[i].fir > ans[i].sec)
      swap(ans[i].fir, ans[i].sec);
    t[ans[i].fir].pb(ans[i].sec);
    t[ans[i].sec].pb(ans[i].fir);
    d.make_set(ans[i].fir, ans[i].sec);
  }
  if (d.sz[d.find_set(1)] != n)
  {
    return 0;
  }
  vector<pi> dale;
  for (int i = 1; i <= n; i++)
  {
    for (int a = 0; a < t[i].size(); a++)
    {
      dale.pb({min(t[i][a], i), max(t[i][a], i)});
      for (int b = a + 1; b < t[i].size(); b++)
      {
        dale.pb({min(t[i][a], t[i][b]), max(t[i][a], t[i][b])});
        if (dale.size() > (edges.size() * 2))
          return 0;
      }
    }
  }
  sort(dale.begin(), dale.end());
  dale.erase(unique(dale.begin(), dale.end()), dale.end());
  if (edges != dale)
    return 0;
  return 1;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  if (m == (n * (n - 1)) / 2)
  {
    for (int i = 2; i <= n; i++)
      cout << 1 << " " << i << endl;
    return 0;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    if (u > v)
      swap(u, v);
    edges.pb({u, v});
    adj[u].insert(v);
    adj[v].insert(u);
    g[u].pb(v);
    g[v].pb(u);
  }
  sort(edges.begin(), edges.end());
  vector<int> ord = PEO();
  if (!is_chordal(ord))
  {
    cout << "*\n";
    return 0;
  }
  vector<int> parent(n + 1, -1);
  vector<bool> vis(n + 1, 0);
  vector<pi> ans, ans2;
  int non_vis = n;
  auto rem = [&](int x)
  {
    vis[x] = 1;
    non_vis--;
    for (auto const &i : adj[x])
    {
      adj[i].erase(x);
    }
    adj[x].clear();
  };
  vector<vector<int>> aux(n + 1);
  for (auto const &x : ord)
  {
    if (vis[x])
    {
      continue;
    }
    vector<int> leaf;
    leaf.pb(x);
    for (auto const &i : adj[x])
    {
      if (!vis[i] && adj[i].size() == adj[x].size())
        leaf.pb(i);
    }
    for (auto const &i : leaf)
    {
      for (auto const &j : g[i])
      {
        if (vis[j] && parent[j] == -1)
          aux[i].pb(j);
      }
    }
    // for (auto const &i : leaf)
    //   cout << i << " ";
    // cout << endl;
    // cout << "--------" << endl;
    // for (auto [a, b] : ans)
    //   cout << a << " " << b << endl;
    // cout << "--------" << endl;
    if (non_vis == leaf.size()) // ficou uma estrela no final, preciso resolver sapeste
    {
      sort(leaf.begin(), leaf.end());
      vector<int> todo;
      vector<int> cnt(n + 1, 0);
      for (int i = 1; i <= n; i++)
      {
        if (vis[i] && parent[i] == -1)
        {
          todo.pb(i);
          for (auto const &j : g[i])
          {
            if (binary_search(leaf.begin(), leaf.end(), j))
              cnt[j]++;
          }
        }
      }
      int mx = *max_element(cnt.begin(), cnt.end());
      int tot = 0;
      for (auto const &l : leaf)
      {
        if (cnt[l] == mx) // tenta deixar l sendo o centro da estrela
        {
          tot++;
          if (tot >= 3)
          {
            cout << "*\n";
            exit(0);
          }
          vector<pi> ed = ans;
          for (auto const &i : leaf)
          {
            if (l != i)
              ed.pb({i, l});
          }
          for (auto const &i : todo)
          {
            for (auto const &j : g[i])
            {
              if (binary_search(leaf.begin(), leaf.end(), j) && j != l)
                ed.pb({j, i});
            }
          }
          if (ed.size() == (n - 1) && check(ed))
          {
            for (auto [a, b] : ed)
            {
              cout << a << " " << b << endl;
            }
            exit(0);
          }
        }
      }
      break;
    }
    else
    {
      for (auto const &i : leaf)
      {
        for (auto const &j : aux[i])
        {
          parent[j] = i;
          ans.pb({i, j});
        }
        rem(i);
      }
    }
  }
  cout << "*\n";
  return 0;
}
// o grafo g^2 eh um grafo chordal
// um grafo chordal eh quando existe uma ordem de eliminacao perfeita
// ou seja: eh possivel ordenar os vertices em uma ordem v1, v2, ..., vn
// tal que
// se eu estou removendo o vertice v_i
// e seja os vizinhos de v_i que aparecem em posicoes j, k, l, ... tal que j, k, l, ... > i
// ou seja, consideramos os vizinhos que sao eliminados depois pela dada ordem descrita
// esses vizinhos foram uma clique!

// mas ai dado isso, como achar essa ordem de eliminacao perfeita de um grafo chordal?
// com lex bfs!