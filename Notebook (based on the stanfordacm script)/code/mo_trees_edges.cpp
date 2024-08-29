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
#define MAXN 200001
#define mod 998244353

struct qry
{
  int l, r, ini, id;
};

int n, q;
vector<pi> adj[MAXN];
int v[MAXN];
int cnt[MAXN];
int freq[MAXN];
int in_block[MAXN];
int tin[MAXN];
int tout[MAXN];
int depth[MAXN];
int up[MAXN][25];
vector<int> t;
vector<qry> qq;

void dfs(int s, int p, int par_edge)
{
  v[s] = par_edge;
  tin[s] = t.size();
  up[s][0] = p;
  for (int i = 1; i < 25; i++)
    up[s][i] = up[up[s][i - 1]][i - 1];
  t.pb(s);
  for (auto const &i : adj[s])
  {
    if (i.fir == p)
      continue;
    depth[i.fir] = depth[s] + 1;
    dfs(i.fir, s, i.sec);
  }
  tout[s] = t.size();
  t.pb(s);
}
bool is(int u, int v)
{
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}
int lca(int u, int v)
{
  if (is(u, v))
    return u;
  if (is(v, u))
    return v;
  for (int i = 24; i >= 0; i--)
  {
    if (!is(up[u][i], v))
      u = up[u][i];
  }
  return up[u][0];
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    adj[b].pb({a, c});
  }
  dfs(0, 0, 0);
  for (int i = 0; i < q; i++)
  {
    int x, y;
    cin >> x >> y;
    x--, y--;
    int l = lca(x, y);
    if (tin[x] > tin[y])
      swap(x, y);
    if (l == x)
      qq.pb({tin[x], tin[y], x, i});
    else
      qq.pb({tout[x], tin[y], -1, i});
  }
  int block = sqrt(n) + 1;
  auto cmp = [&](qry x, qry y)
  {
    if (x.l / block != y.l / block)
      return x.l / block < y.l / block;
    return x.r < y.r;
  };
  sort(qq.begin(), qq.end(), cmp);
  vector<int> ans(q);
  int cl = 0, cr = 0, resp = 0;
  auto add2 = [&](int x)
  {
    if (v[x] >= MAXN)
      return;
    freq[v[x]]++;
    if (freq[v[x]] == 1)
      in_block[v[x] / block]++;
  };
  auto rem2 = [&](int x)
  {
    if (v[x] >= MAXN)
      return;
    freq[v[x]]--;
    if (freq[v[x]] == 0)
      in_block[v[x] / block]--;
  };
  auto add = [&](int x)
  {
    cnt[x]++;
    if (cnt[x] == 2)
      rem2(x);
    else
      add2(x);
  };
  auto rem = [&](int x)
  {
    cnt[x]--;
    if (cnt[x] == 1)
      add2(x);
    else
      rem2(x);
  };
  for (int i = 0; i < q; i++)
  {
    int idx = qq[i].id;
    int l = qq[i].l;
    int r = qq[i].r;
    int ini = qq[i].ini;
    while (cl < l)
      rem(t[cl++]);
    while (cl > l)
      add(t[--cl]);
    while (cr <= r)
      add(t[cr++]);
    while (cr > r + 1)
      rem(t[--cr]);
    if (ini != -1)
      rem(ini);
    for (int b = 0;; b++)
    {
      if (in_block[b] != block)
      {
        ans[idx] = b * block;
        while (freq[ans[idx]])
          ans[idx]++;
        break;
      }
    }
    if (ini != -1)
      add(ini);
  }
  for (auto const &i : ans)
    cout << i << endl;
  return 0;
}
// https://codeforces.com/gym/100962/attachments (problema F)
// mo em arvore com peso nos edges

// nesse problema em especifico: dado uma arvore, responder queries de mex
// no caminho entre u e v, considerando os pesos de arestas no caminho de u pra v

// mo em arvores
// acha o euler tour da arvore com tin e tout
// desconsidera no mo os indices duplicados no range
// e bem parecido com o de peso nos vertices
// considera v[i] -> peso do edge que liga ao meu pai na arvore
// dai pra query com o lca == u, nao tenho que considerar v[u] ([tin[u], tin[v]], dps removendo v[u])
// e pra query com o lca != u, so fazer ela normalmente ([tout[u], tin[v]])
