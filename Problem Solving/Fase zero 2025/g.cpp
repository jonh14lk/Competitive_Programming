#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define MAXN 200005

int n, p;
vector<int> adj[MAXN];
int dep[MAXN];
int par[MAXN];
int ans[MAXN];
int mask[MAXN];
bool on_any_path[MAXN];
int cnt[5];
int inicnt[5];
vector<int> path[5];
int cnt_mask[1 << 5];
int tot_mask[1 << 5];

void dfs(int s, int p)
{
  for (auto const &x : adj[s])
  {
    if (x != p)
    {
      par[x] = s;
      dep[x] = dep[s] + 1;
      dfs(x, s);
    }
  }
}
void get_path(int u, int v, int id) // pegar os vertices do caminho de u pra v na ordem
{
  if (u == v)
  {
    path[id].pb(u);
    if (path[id].size() > 5) // impossivel
    {
      cout << "-1\n";
      exit(0);
    }
  }
  else if (dep[u] > dep[v])
  {
    path[id].pb(u);
    if (path[id].size() > 5) // impossivel
    {
      cout << "-1\n";
      exit(0);
    }
    get_path(par[u], v, id);
  }
  else
  {
    get_path(u, par[v], id);
    path[id].pb(v);
    if (path[id].size() > 5) // impossivel
    {
      cout << "-1\n";
      exit(0);
    }
  }
}
bool hall() // checa se o perfect matching existe
{
  for (int mask = 1; mask < (1 << 5); mask++)
  {
    int x = 0;
    for (int i = 0; i < 5; i++)
    {
      if (mask & (1 << i))
        x += cnt[i];
    }
    if (x < tot_mask[mask])
      return 0;
  }
  return 1;
}
void fill_rem_vertices() // preencher a resposta para os vertices que nao estao em nenhum dos paths
{
  for (int x = 0; x < n; x++)
  {
    if (ans[x] == -1)
    {
      for (int m = 0; m < (1 << 5); m++)
      {
        if ((m & mask[x]) == mask[x])
          tot_mask[m]--;
      }
      for (int val = 0; val < 5; val++) // definir o valor de ans[x]
      {
        if ((mask[x] & (1 << val)) && cnt[val] > 0)
        {
          cnt[val]--;
          if (hall()) // se ainda existir perfect matching, faz com que ans[x] = val
          {
            ans[x] = val;
            break;
          }
          cnt[val]++;
        }
      }
    }
  }
}
void check_valid_solution()
{
  for (int i = 0; i < p; i++)
  {
    for (int x = 1; x < path[i].size(); x++)
    {
      assert(ans[path[i][x - 1]] < ans[path[i][x]]);
    }
  }
  vector<int> cnt2(5, 0);
  for (int i = 0; i < n; i++)
  {
    cnt2[ans[i]]++;
    assert((ans[i] + 1) >= 1);
    assert((ans[i] + 1) <= 5);
    assert(mask[i] & (1 << ans[i]));
  }
  for (int i = 0; i < 5; i++)
  {
    assert(cnt2[i] == inicnt[i]);
  }
}
void solve(int path_id, int curr, int last)
{
  if (path_id == p) // um possivel jeito de preencher os vertices que aparecem em pelo menos um path
  {
    if (hall()) // se achamos uma solucao valida gg
    {
      fill_rem_vertices();
      for (int i = 0; i < n; i++)
        cout << ans[i] + 1 << " \n"[i == (n - 1)];
      check_valid_solution();
      exit(0);
    }
    return;
  }
  if (curr == path[path_id].size()) // terminei um path
  {
    return solve(path_id + 1, 0, -1);
  }
  int x = path[path_id][curr];
  if (ans[x] != -1)
  {
    if (ans[x] > last)
      solve(path_id, curr + 1, ans[x]);
  }
  else
  {
    for (int val = last + 1; val < 5; val++) // definir o valor de ans[x]
    {
      if ((mask[x] & (1 << val)) && cnt[val] > 0)
      {
        cnt[val]--;
        ans[x] = val;
        solve(path_id, curr + 1, ans[x]);
        ans[x] = -1;
        cnt[val]++;
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < 5; i++) // quantos caras iguais a i vai ter na solucao
  {
    cin >> cnt[i];
    inicnt[i] = cnt[i];
  }
  for (int i = 0; i < n; i++) // pro vertice i, quais valores ele pode ter
  {
    int sz;
    cin >> sz;
    while (sz--)
    {
      int x;
      cin >> x;
      x--;
      mask[i] |= (1 << x);
    }
  }
  for (int i = 1; i < n; i++) // ler a arvore
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  dep[0] = 0;
  dfs(0, -1);
  cin >> p;
  for (int i = 0; i < p; i++) // ler os paths importantes
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    get_path(u, v, i);
    for (auto const &j : path[i])
      on_any_path[j] = 1;
  }
  for (int i = 0; i < n; i++)
  {
    if (!on_any_path[i])
      cnt_mask[mask[i]]++;
  }
  for (int m = 0; m < (1 << 5); m++)
  {
    for (int s = m; s; s = (s - 1) & m) // soma dos cnt_mask de todas as submasks
      tot_mask[m] += cnt_mask[s];
  }
  memset(ans, -1, sizeof(ans));
  solve(0, 0, -1);
  cout << "-1\n"; // caso eu nao tenha encontrado nenhuma solucao
  return 0;
}