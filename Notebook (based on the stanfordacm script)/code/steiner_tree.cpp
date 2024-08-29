#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 4007
#define mod 998244353

const int inf = 1e18;

int n, m, k, sz;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
int a[101][101];

vector<int> g[201];
int w[201][201];
int dist[201][201];
int par_floyd[201][201];
int dp[201][1 << 8];
char anss[201][201];
vector<pi> par[201][1 << 8];
int pos[10];

int steiner()
{
  // floyd warshall
  for (int i = 0; i < sz; i++)
  {
    for (int j = 0; j < sz; j++)
    {
      if (i == j)
      {
        dist[i][j] = 0;
      }
      else
      {
        dist[i][j] = w[i][j];
        par_floyd[i][j] = j;
      }
    }
  }
  for (int k = 0; k < sz; k++)
  {
    for (int i = 0; i < sz; i++)
    {
      for (int j = 0; j < sz; j++)
      {
        if (dist[i][j] > dist[i][k] + dist[k][j])
        {
          dist[i][j] = dist[i][k] + dist[k][j];
          par_floyd[i][j] = par_floyd[i][k];
        }
      }
    }
  }
  for (int i = 0; i < sz; i++)
  {
    for (int j = 0; j < (1 << k); j++)
      dp[i][j] = inf;
  }
  for (int i = 0; i < k; i++)
  {
    for (int j = 0; j < sz; j++)
    {
      dp[j][1 << i] = dist[pos[i]][j];
      par[j][1 << i] = {{pos[i], 0}};
    }
  }
  for (int mask = 2; mask < (1 << k); mask++)
  {
    for (int i = 0; i < sz; i++)
    {
      for (int mask2 = mask; mask2 > 0; mask2 = (mask2 - 1) & mask)
      {
        int mask3 = mask ^ mask2;
        if (dp[i][mask] > dp[i][mask2] + dp[i][mask3])
        {
          dp[i][mask] = dp[i][mask2] + dp[i][mask3];
          par[i][mask] = {{i, mask2}, {i, mask3}};
        }
      }
      for (int j = 0; j < sz; j++)
      {
        if (dp[j][mask] > dp[i][mask] + dist[i][j])
        {
          dp[j][mask] = dp[i][mask] + dist[i][j];
          par[j][mask] = {{i, mask}};
        }
      }
    }
  }
  // preciso somar a[i / m][i % m] pq tou usando a[i][j]
  // como peso de uma aresta (i, j) -> (x, y)
  // mas eh especifico para esse problema do garden
  int ans = inf, best = -1;
  for (int i = 0; i < sz; i++)
  {
    int curr = a[i / m][i % m] + dp[i][(1 << k) - 1];
    if (curr < ans)
    {
      ans = curr;
      best = i;
    }
  }
  // recuperar resposta
  queue<pi> q;
  q.push({best, (1 << k) - 1});
  while (!q.empty())
  {
    auto [i, mask] = q.front();
    q.pop();
    anss[i / m][i % m] = 'X';
    for (auto [j, mask2] : par[i][mask])
    {
      // marcar o caminho de j para i feito pelo floyd warshall
      int st = j, en = i;
      while (st != en)
      {
        st = par_floyd[st][en];
        anss[st / m][st % m] = 'X';
      }
      q.push({j, mask2});
    }
  }
  return ans;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> a[i][j];
      anss[i][j] = '.';
    }
  }
  sz = (n * m);
  for (int i = 0; i < sz; i++)
  {
    for (int j = 0; j < sz; j++)
      w[i][j] = inf;
  }
  // montando o grafo
  // (i, j) -> (x, y) com peso a[i][j]
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      for (int d = 0; d < 4; d++)
      {
        int x = i + dx[d];
        int y = j + dy[d];
        if (x >= 0 && x < n && y >= 0 && y < m)
          w[(i * m) + j][(x * m) + y] = a[i][j];
      }
    }
  }
  // posicoes importantes
  for (int i = 0; i < k; i++)
  {
    int x, y;
    cin >> x >> y;
    x--, y--;
    pos[i] = (x * m) + y;
  }
  cout << steiner() << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      cout << anss[i][j];
    cout << endl;
  }
  return 0;
}
// https://codeforces.com/problemset/problem/152/E
// dada uma matriz representando um jardim
// a posicao (i, j) tem a[i][j] flores
// com isso, quero cobrir algumas posicoes com concreto
// quando cobrimos uma posicao (i, j) com concreto, "matamos" as a[i][j] flores daquela posicao
// existem k <= 7 posicoes importantes, que devem ser cobertas com concreto
// alem disso, posso cobrir qualquer outra posicao com concreto
// alem disso, para duas posicoes a e b que sao importantes, deve existir um caminho
// de a ate b passando somente por posicoes cobertas por concreto.
// quero minimizar o numero de flores mortas, satisfazendo essas condicoes

// o que queremos nesse caso, eh uma steiner tree
// dado um grafo, com peso nas arestas
// e um subconjunto de vertices
// queremos achar uma arvore de menor peso que contenha todos os vertices do subconjunto
// mas essa arvore pode conter tambem outros vertices que nao estao no subconjunto
// minimizando o peso total das arestas da arvore

// um outro problema de steiner tree: https://codeforces.com/gym/101908/problem/J