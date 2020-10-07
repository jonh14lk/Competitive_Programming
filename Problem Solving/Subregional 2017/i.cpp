#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

int n, c;
vector<int> gold(MAXN);
vector<int> subtree_gold(MAXN);
vector<int> subtree_cost(MAXN);
vector<int> dp(MAXN);
vector<pi> adj[MAXN];

void dfs(int s, int f)
{
  subtree_gold[s] = gold[s]; // soma acumulada da quantidade de ouro na subtree de s
  subtree_cost[s] = 0;       // soma acumulada do custo das arestas na subtree de s
  for (auto const &v : adj[s])
  {
    if (v.fir != f)
    {
      dfs(v.fir, s); // apenas calcule isso
      subtree_cost[s] += v.sec;
      subtree_cost[s] += subtree_cost[v.fir];
      subtree_gold[s] += subtree_gold[v.fir];
    }
  }
}
void dfs2(int s, int f)
{
  for (auto const &v : adj[s])
  {
    if (v.fir != f)
    {
      dfs2(v.fir, s);
      int need = subtree_gold[v.fir] / c; // quantas vezes eu irei ter que passar pela aresta [s - v.fir]
      if (subtree_gold[v.fir] % c)        // isso so depende da quantidade de ouro acumulado que existe na subtree de v.fir
        need++;
      dp[s] += v.sec * need; // logo o custo para coletar todo o ouro acumulado na subtree de s eh:
      dp[s] += dp[v.fir];    // a soma acumulada de (quantas vezes eu preciso passar * custo) para cada aresta da subtree de s
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> c;
  for (int i = 0; i < n; i++)
    cin >> gold[i];
  for (int i = 0; i < n - 1; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    adj[b].pb({a, c});
  }
  dfs(0, -1);
  dfs2(0, -1);
  dp[0] = dp[0] << 1;
  cout << dp[0] << endl;
}