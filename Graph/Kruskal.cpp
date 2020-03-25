// Algoritimo de kruskal - Achar a mst

// 1 - listar todas as arestas em ordem crescente.

// 2 - Cada aresta liga dois vértices x e y, checar se eles já estão na mesma componente conexa
// (aqui, consideramos apenas as arestas já colocadas na árvore).

// 3 - Se x e y estão na mesma componente, ignoramos a aresta e continuamos o procedimento
// (se a usássemos, formaríamos um ciclo). Se estiverem em componentes distintas, colocamos a aresta
//na árvore e continuamos o procedimento.

// OBS: como a prioridade eh ordenar pelas menores distancias, basta botar o custo da aresta como
// first no vector das arestas para poder ordenar

// em suma: ordeno as arestas em ordem decrescente com prioridade no custo, depois para cada aresta,
// se o find(x) != find(y) sendo x e y os vertices das arestas, eu adiciono eles a mst e dou um join
// nos dois, como as arestas tao ordenadas em ordem decrescente, o primeiro que eu pego
// eh necessariamente a melhor opçao e assim a mst eh formada.

#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 100001

int n, m, a, b, c;
vector<pii> ar;
vector<pii> mst;
int pai[MAXN];
int peso[MAXN];

int find(int x)
{
  if (pai[x] == x)
  {
    return x;
  }
  return pai[x] = find(pai[x]);
}
void join(int a, int b)
{
  a = find(a);
  b = find(b);

  if (peso[a] < peso[b])
  {
    pai[a] = b;
  }
  else if (peso[b] < peso[a])
  {
    pai[b] = a;
  }
  else
  {
    pai[a] = b;
    peso[b]++;
  }
}
void initialize()
{
  for (int i = 1; i <= n; i++)
  {
    pai[i] = i;
  }
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    ar.pb(mp(c, mp(a, b)));
  }

  sort(ar.begin(), ar.end());

  initialize();

  int size = 0;

  for (int i = 0; i < m; i++)
  {
    if (find(ar[i].sec.fir) != find(ar[i].sec.sec))
    {
      join(ar[i].sec.fir, ar[i].sec.sec);
      mst.pb(mp(ar[i].fir, mp(ar[i].sec.fir, ar[i].sec.sec)));
    }
  }

  for (int i = 0; i < mst.size(); i++)
  {
    cout << mst[i].sec.fir << " " << mst[i].sec.sec << " " << mst[i].fir << endl;
  }

  return 0;
}
