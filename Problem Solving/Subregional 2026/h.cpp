#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

int v[MAXN];
bool vis[MAXN];
int val[MAXN];
vector<int> adj[MAXN];

void dfs(int i)
{
  vis[i] = 1;
  for (auto const &j : adj[i])
  {
    if (!vis[j])
    {
      dfs(j);
      if (val[j])
      {
        val[j] ^= 1;
        val[i] ^= 1;
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
  {
    cin >> v[i];
  }
  for (int i = 0; i <= n; i++)
  {
    val[i] = v[i] ^ v[i + 1];
  }
  for (int i = 0; i < m; i++)
  {
    int l, r;
    cin >> l >> r;
    l--, r--;
    adj[l].pb(r + 1);
    adj[r + 1].pb(l);
  }
  for (int i = 0; i <= n; i++)
  {
    if (!vis[i])
      dfs(i);
  }
  for (int i = 0; i <= n; i++)
  {
    if (val[i])
    {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  return 0;
}
// muda v[l] e muda v[r + 1]
// se pensar na transformacao de criar um novo array em que cada elemento eh v[i] ^ v[i + 1]
// eh o problema classico do usp tryouts de remover arestas num grafo pra que o grau de todo mundo seja par