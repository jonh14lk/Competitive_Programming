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
#define MAXN 200005
#define mod 1000000007

bool needs[MAXN];
int dp0[MAXN];
multiset<int> dp[MAXN];

struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;
  vector<int> sum;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    sum.assign(n, 0);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
      sum[i] = needs[i];
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  int make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      sum[y] += sum[x];
      tot--;
    }
    return y;
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
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 0; i < n; i++)
    {
      needs[i] = 0;
      dp[i].clear();
    }
    for (int i = 0; i < p; i++)
    {
      int x;
      cin >> x;
      x--;
      needs[x] = 1;
    }
    vector<pii> edges;
    for (int i = 0; i < m; i++)
    {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      edges.pb({w, {u, v}});
    }
    for (int i = 0; i < n; i++)
    {
      dp[i].insert(0);
      dp0[i] = 0;
    }
    sort(edges.begin(), edges.end());
    dsu d(n);
    for (auto const &ii : edges)
    {
      int w = ii.fir;
      auto [u, v] = ii.sec;
      if (d.find_set(u) != d.find_set(v))
      {
        u = d.find_set(u);
        v = d.find_set(v);
        if (d.sz[u] > d.sz[v])
        {
          swap(u, v);
        }
        // problema brabo e educational
        // o que funcionava ate a hard version era algo tipo isso
        //  for (int i = 0; i <= szu; i++)
        // {
        //   for (int j = 0; j <= szv; j++)
        //     new_dp[i + j] = min(new_dp[i + j], dp[u][i] + dp[v][j]);
        // }
        // isso eh uma (min, +) convolution
        // e ambas as sequencias satisfazem:
        // dp[i + 1] - dp[i] <= dp[i] - dp[i - 1]
        // dai pra fazer a ideia desse blog, descrita em (max, +) convolution
        // https://codeforces.com/blog/entry/98663
        // que eh basicamente ir "mergindo" as slopes de forma gulosa
        // entretanto a unica coisa que muda eh que em cada iteracao desse kruskal
        // temos que setar o valor de dp[0] para algo diferente antes de fzr a (min, +) convolution
        // ai tem que refletir isso no multiset das diferencas
        {
          int ini = *dp[u].begin();
          dp[u].erase(dp[u].find(ini));
          int new_dp0 = d.sum[u] * w;
          // se antes diferenca era dp[1] - dp[0]
          // eu aumentei o dp[0] por x
          // agr vai ser (dp[1] - dp[0]) - x
          int x = new_dp0 - dp0[u];
          dp[u].insert(ini - x);
          dp0[u] = new_dp0;
        }
        {
          int ini = *dp[v].begin();
          dp[v].erase(dp[v].find(ini));
          int new_dp0 = d.sum[v] * w;
          // se antes diferenca era dp[1] - dp[0]
          // eu aumentei o dp[0] por x
          // agr vai ser (dp[1] - dp[0]) - x
          int x = new_dp0 - dp0[v];
          dp[v].insert(ini - x);
          dp0[v] = new_dp0;
        }
        for (auto const &x : dp[u])
        {
          dp[v].insert(x);
        }
        dp0[v] += dp0[u];
        dp[u].clear();
        d.make_set(u, v);
      }
    }
    int par = d.find_set(0);
    int x = dp0[par];
    // como eh uma min+ convolution, vai da menor slope pra maior slope
    for (auto const &val : dp[par])
    {
      x += val;
      cout << x << " ";
    }
    cout << endl;
  }
  return 0;
}
// https://codeforces.com/contest/2021/problem/E3