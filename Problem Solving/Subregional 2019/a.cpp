#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 10001

bool visited[MAXN];
vector<int> adj[MAXN];
vector<pii> cir;

bool intersect(pii a, pii b) // insersecção circulo com circulo
{
  double dist = sqrt(pow((a.fir.fir - b.fir.fir), 2) + pow((a.fir.sec - b.fir.sec), 2));
  double raios = a.sec + b.sec;
  return (dist <= raios); // apenas olhe se a distancia entre os centros é menor ou igual a soma dos raios
}
void dfs(int s)
{
  visited[s] = true;
  for (auto const &i : adj[s])
    if (!visited[i])
      dfs(i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < k; i++)
  {
    int x, y, s;
    cin >> x >> y >> s;
    cir.pb({{x, y}, s});
  }
  for (int i = 0; i < k; i++)
    for (int j = i + 1; j < k; j++)
      if (intersect(cir[i], cir[j])) // se dois circulos se intersectam, adiciono uma aresta entre eles
        adj[i].pb(j), adj[j].pb(i);
  for (int i = 0; i < k; i++)
    if (abs(cir[i].fir.fir - n) <= cir[i].sec) // se algum circulo se intersecta com a extremidade de baixo da sala
      adj[i].pb(k), adj[k].pb(i);
  for (int i = 0; i < k; i++)
    if (abs(cir[i].fir.fir - 0ll) <= cir[i].sec) // se algum circulo se intersecta com a extremidade de cima da sala
      adj[i].pb(k + 1), adj[k + 1].pb(i);
  for (int i = 0; i < k; i++)
    if (abs(cir[i].fir.sec - m) <= cir[i].sec) // se algum circulo se intersecta com a extremidade direita da sala
      adj[i].pb(k + 2), adj[k + 2].pb(i);
  for (int i = 0; i < k; i++)
    if (abs(cir[i].fir.sec - 0ll) <= cir[i].sec) // se algum circulo se intersecta com a extremidade esquerda da sala
      adj[i].pb(k + 3), adj[k + 3].pb(i);
  dfs(k); // de baixo
  if (visited[k + 1] || visited[k + 2])
  {
    cout << "N\n";
    return 0;
  }
  dfs(k + 3); // da direita
  if (visited[k + 1] || visited[k + 2])
  {
    cout << "N\n";
    return 0;
  }
  cout << "S\n";
  return 0;
}
// se for possivel sair da extremidade de baixo ate a de cima ou direita
// ou se for possivel sair da extremidade esquerda ate a de cima ou direita
// apenas passando por celulas "invalidas", a resposta eh nao
// caso nenhum dos dois são validos, a resposta eh sim