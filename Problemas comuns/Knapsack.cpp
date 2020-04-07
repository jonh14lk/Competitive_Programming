//O problema mais clássico de Programação Dinâmica talvez seja o Knapsack.
//De maneira geral, um ladrão irá roubar uma casa com uma mochila
//que suporta um peso s. Ele vê n objetos na casa e sabe estimar o peso pi​ ​​e o valor vi ​​
//de cada objeto i. Com essas informações, qual o maior valor que o ladrão pode roubar sem rasgar sua mochila?
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
#define MAXN 1001
#define INF 1000000000

int n, l;
int value[MAXN];
int peso[MAXN];
int dp[MAXN][MAXN];

int knapsack(int i, int limit)
{
  if (dp[i][limit] >= 0) // se ja foi calculado
  {
    return dp[i][limit];
  }

  if (i == n or !limit) // se chegou no fim do array ou chegou no limite
  {
    return dp[i][limit] = 0;
  }

  int nao_coloca = knapsack(i + 1, limit); // recursivamente pra caso eu nao coloque o objeto i

  if (peso[i] <= limit) // se eu consigo botar o objeto i
  {
    int coloca = value[i] + knapsack(i + 1, limit - peso[i]);
    return dp[i][limit] = max(coloca, nao_coloca);
  }

  return dp[i][limit] = nao_coloca;
}
signed main()
{
  cin >> l >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> peso[i] >> value[i];
  }
  memset(dp, -1, sizeof(dp));
  cout << knapsack(0, l) << endl;
  return 0;
}
