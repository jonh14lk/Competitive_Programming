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
#define MAXN 1000006
#define mod 1000000007

const int magic = 150;

int n;
int b[8005];
int lastb[8005];
vector<int> adj[8005];
int v[8005][8005];
bool vis[8005];
int val[8005];
char c[MAXN];
int x[MAXN];
int y[MAXN];
bool updated[8005];

void dfs(int i)
{
  if (vis[i])
    return;
  vis[i] = 1;
  v[i][i] = (v[i][i] + 1) % mod;
  for (auto const &j : adj[i])
  {
    dfs(j);
    for (int x = 0; x < n; x++)
    {
      v[i][x] += v[j][x];
      v[i][x] %= mod;
    }
  }
}
void dfs2(int i)
{
  if (vis[i])
    return;
  vis[i] = 1;
  val[i] = b[i] % mod;
  for (auto const &j : adj[i])
  {
    dfs2(j);
    val[i] += val[j];
    val[i] %= mod;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }
  int m;
  cin >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
  }
  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i);
  }
  auto update_all = [&]()
  {
    for (int i = 0; i < n; i++)
    {
      vis[i] = 0;
      val[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
      if (!vis[i])
        dfs2(i);
    }
  };
  update_all();
  int q;
  cin >> q;
  for (int i = 1; i <= q; i++)
  {
    cin >> c[i];
    if (c[i] == 'Q')
    {
      cin >> x[i];
      x[i]--;
    }
    else
    {
      cin >> x[i] >> y[i];
      x[i]--;
    }
  }
  int ans = 0, id = 1;
  for (int l = 1; l <= q; l += magic)
  {
    int r = min(q, l + magic - 1);
    // resolver as queries entre [l, r]
    for (int i = l; i <= r; i++)
    {
      if (c[i] == 'Q')
      {
        int curr = (val[x[i]] * id) % mod;
        ans = (ans + curr) % mod;
        id++;
      }
      else
      {
        for (int j = i; j <= r; j++) // atualizo so as posicoes q tao no bloco
        {
          if (!updated[x[j]])
          {
            val[x[j]] += (v[x[j]][x[i]] * (y[i] - b[x[i]])) % mod;
            val[x[j]] = (val[x[j]] + mod) % mod;
            updated[x[j]] = 1;
          }
        }
        b[x[i]] = y[i];
        for (int j = i; j <= r; j++)
        {
          updated[x[j]] = 0;
        }
      }
    }
    update_all();
  }
  cout << ans << endl;
  return 0;
}
// achar uma matriz de tamanho 8000
// v[i][j] - qual vai ser a contribuicao de j no f(i)
