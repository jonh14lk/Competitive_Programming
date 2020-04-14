// LCA sem dp
// ache o nó que é ancestral comum de x e de y e está o mais longe possível da raiz.
// 1 - definir para cade vértice, seu nível de profundidade (igual a sua distância até a raiz) - DFS
// 2 - definir o pai de um vértice, que é o vértice adjacente a ele que possui um nível menor. - DFS
// 3 - Tendo apenas essas informações, já é possível descobrir o LCA de dois vértices (forma lenta)
#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 200001

int n, m;
int father[MAXN];
int level[MAXN];
vector<int> adj[MAXN];

int lca(int a, int b)
{
  while (a != b)
  {
    if (level[a] > level[b])
      a = father[a];
    else
      b = father[b];
  }
  return a;
}
void dfs(int u)
{
  for (int i = 0; i < adj[u].size(); i++)
  {
    int v = adj[u][i];
    if (level[v] == -1)
    {
      father[v] = u;
      level[v] = level[u] + 1;
      dfs(v);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  int vv, uu;
  cin >> vv >> uu;
  memset(father, -1, sizeof(father));
  memset(level, -1, sizeof(level));
  level[1] = 0;
  dfs(1);
  cout << lca(vv, uu) << endl;
  return 0;
}
