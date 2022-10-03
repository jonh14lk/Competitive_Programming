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
#define MAXN 100005
#define mod 1000000007

vector<int> adj[MAXN];
vector<int> v[MAXN];
int c[MAXN];
int cnt[MAXN];
int sz[MAXN];

void dfs_sz(int x, int p)
{
  sz[x] = 1;
  for (auto const &i : adj[x])
  {
    if (i != p)
    {
      dfs_sz(i, x);
      sz[x] += sz[i];
    }
  }
}
void modify(int c, int val)
{
  cnt[c] += val;
}
void dfs(int x, int p, bool keep)
{
  int best = -1, big_child = -1;
  for (auto const &i : adj[x])
  {
    if (i != p && sz[i] > best)
    {
      best = sz[i];
      big_child = i;
    }
  }
  for (auto const &i : adj[x])
  {
    if (i != p && i != big_child)
      dfs(i, x, 0);
  }
  if (big_child != -1)
  {
    dfs(big_child, x, 1);
    swap(v[x], v[big_child]); // O(1)
  }
  v[x].pb(x);
  modify(c[x], 1); // adiciona
  for (auto const &i : adj[x])
  {
    if (i != p && i != big_child)
    {
      for (auto const &j : v[i])
      {
        v[x].pb(j);
        modify(c[j], 1); // adiciona
      }
    }
  }
  // a cor c aparece cnt[c] vezes na subtree de x
  // dai vc pode fazer algo tendo essa informacao
  // seja responser queries ou algo do tipo aqui
  if (!keep)
  {
    for (auto const &i : v[x])
      modify(c[i], -1); // remove
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> c[i];
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  dfs_sz(0, -1);
  dfs(0, -1, 0);
  cout << endl;
}
// https://codeforces.com/blog/entry/44351
// https://codeforces.com/blog/entry/67696

// problema motivacao:
// dada uma arvore
// cada vertice tem uma cor
// tenho consultas do tipo: quantos caras na subtree de v tem cor == x
// com sack da pra resolver isso em O(n * log(n)) (complexidade do dfs do sack)

// para outros problemas, basta mudar a funcao modify
// muito util em problemas em que vc precisa guardar algo da subarvore de v, para todo v
// seja pra resolver queries offline ou algo do tipo