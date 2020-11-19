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
#define DEBUG 0
#define MAXN 106
#define mod 2
#define EPS 1e-9

bitset<MAXN> ans;

int gauss(vector<bitset<MAXN>> a)
{
  int n = a.size(), m = a[0].size() - 1, ret = 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++)
  {
    for (int i = row; i < n; i++)
    {
      if (a[i][col])
      {
        swap(a[i], a[row]);
        break;
      }
    }
    if (!a[row][col])
      continue;
    where[col] = row;
    for (int i = 0; i < n; i++)
      if (i != row && a[i][col])
        a[i] ^= a[row];
    ++row;
  }
  for (int i = 0; i < m; i++)
  {
    if (where[i] != -1)
      ans[i] = (a[where[i]][m] / a[where[i]][i]);
    else
      ret = 2;
  }
  for (int i = 0; i < n; i++)
  {
    double sum = 0;
    for (int j = 0; j < m; j++)
      sum += (ans[j] * a[i][j]);
    if (abs(sum - a[i][m]) > EPS)
      ret = 0;
  }
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<bitset<MAXN>> a(n);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    a[u][v] = 1;
    a[v][u] = 1;
  }
  for (int i = 0; i < n; i++)
  {
    int sum = 0;
    for (int j = 0; j < n; j++)
      sum += a[i][j];
    if (sum & 1)
    {
      a[i][i] = 1;
      a[i][MAXN - 1] = 0;
    }
    else
    {
      a[i][MAXN - 1] = 1;
    }
  }
  if (DEBUG)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < MAXN; j++)
        cout << a[i][j] << " ";
      cout << endl;
    }
  }
  (gauss(a) != 0) ? cout << "Y\n" : cout << "N\n";
  return 0;
}
// grupo 0 e grupo 1
// xi = grupo[i]
// podemos escrever a solucao como um sistema de equacoes:
// se a adj list de um vertice tem tamanho par
// e seja os vertices dessa adj list a,b,c...
// logo metade dos vizinhos serão do grupo 1 e a outra metade do grupo 2
// xa ^ xb ^ xc ^ ... = 1
// se a adj list de um vertice tem tamanho impar
// e seja os vertices dessa adj list a,b,c...
// logo (metade + 1) vertices irão pertencer a um grupo e o resto a outro grupo
// xi ^ xa ^ xb ^ xc ^ ... = 0
// ao final, se essa equacao tiver uma ou multiplas solucoes
// a resposta eh sim
// o xor nesse caso, pode ser represntado como a soma modulo 2
