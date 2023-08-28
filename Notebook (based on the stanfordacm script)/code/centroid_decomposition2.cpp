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
#define mod 998244353

int n, k, resp;
vector<int> adj[MAXN];
vector<int> cnt;

namespace cd
{
  int sz;
  vector<int> subtree_size;
  vector<bool> visited;

  void dfs(int s, int f)
  {
    sz++;
    subtree_size[s] = 1;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
      {
        dfs(v, s);
        subtree_size[s] += subtree_size[v];
      }
    }
  }
  int get_centroid(int s, int f)
  {
    bool is_centroid = true;
    int heaviest_child = -1;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
      {
        if (subtree_size[v] > sz / 2)
          is_centroid = false;
        if (heaviest_child == -1 || subtree_size[v] > subtree_size[heaviest_child])
          heaviest_child = v;
      }
    }
    return (is_centroid && sz - subtree_size[s] <= sz / 2) ? s : get_centroid(heaviest_child, s);
  }
  void dfs2(int s, int f, int d)
  {
    while (d >= cnt.size())
      cnt.pb(0);
    cnt[d]++;
    for (auto const &v : adj[s])
    {
      if (v != f && !visited[v])
        dfs2(v, s, d + 1);
    }
  }
  void solve(int s)
  {
    vector<int> tot;
    for (auto const &v : adj[s])
    {
      if (visited[v])
        continue;
      cnt.clear();
      dfs2(v, s, 1);
      for (int i = 1; i < cnt.size(); i++)
      {
        if (k - i < tot.size() && k - i >= 1)
          resp += (cnt[i] * tot[k - i]);
      }
      for (int i = 1; i < cnt.size(); i++)
      {
        while (i >= tot.size())
          tot.pb(0);
        tot[i] += cnt[i];
      }
    }
    if (k < tot.size())
      resp += tot[k];
  }
  int decompose_tree(int s)
  {
    sz = 0;
    dfs(s, s);
    int cend_tree = get_centroid(s, s);
    visited[cend_tree] = true;
    solve(cend_tree);
    for (auto const &v : adj[cend_tree])
    {
      if (!visited[v])
        decompose_tree(v);
    }
    return cend_tree;
  }
  void init()
  {
    subtree_size.resize(n);
    visited.resize(n);
    decompose_tree(0);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  cd::init();
  cout << resp << endl;
  return 0;
}
// https://codeforces.com/contest/161/problem/D
// problema: contar quantos pares de vertices (u, v) existem tal que dist(u, v) = k
// durante a decomposicao
// pega o centroid atual e resolve o problema pra ele
// isso eh:
// para cada centroid que eu achei, devo contar quantos caminhos
// de tamanho k passam por esse centroid
// somando todas essas respostas, a gente tem a resposta final
