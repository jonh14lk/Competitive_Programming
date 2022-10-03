#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1001
#define mod 1000000009

const int inf = 1e18;

int n;
vector<pi> v;
int dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

int solve(int i, int j)
{
  if (j == 0)
    return inf;
  if (i == n)
    return -inf;
  if (vis[i][j])
    return dp[i][j];
  int ans = -inf;
  ans = max(ans, solve(i + 1, j));
  int ot = min(v[i].sec, solve(i + 1, j - 1) - v[i].fir);
  ans = max(ans, ot);
  vis[i][j] = 1;
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    v[i].sec -= v[i].fir;
  }
  auto cmp = [&](pi a, pi b)
  {
    return (a.sec - b.fir) < (b.sec - a.fir);
  };
  sort(v.begin(), v.end(), cmp);
  memset(dp, -1, sizeof(dp));
  int ans = 0;
  for (int i = n; i >= 0; i--)
  {
    if (solve(0, i) >= 0)
    {
      ans = i;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}
// problema:
// existem n caixas, cada uma tem um peso w[i] e uma resistencia r[i]
// voce deve escolher um subset de caixas e empilhar na ordem que vc quiser
// tal que: a soma dos pesos de todas as caixas acima de uma caixa seja menor ou igual a resistencia dessa caixa

// dp[i][j] - estou na caixa i e quero escolher mais j caixas para botar na pilha
// qual a maior resistencia restante que eu posso obter escolhendo essas j caixas

// a grande sacada pra achar a ordenacao otima antes da dp:
// para duas caixas a e b
// quando vai ser stonks botar a antes de b?
// r[a] - w[b] > r[b] - w[a]
// pois a resistencia reestante vai ser maior

// pra demais problemas de exchange argument, essa ideia pode se aplicar
// do tipo, ver o jeito otimo de resolver pro n = 2
// e fazer a ordenacao baseada nisso