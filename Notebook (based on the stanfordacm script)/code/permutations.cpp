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
#define MAXN 300005
#define mod 1000000007

int n;
string s;
int dp[3005][3005];
int sum[3005][3005];

int solve(int i, int j);

void solve2(int i)
{
  if (sum[i][0] != -1)
    return;
  sum[i][0] = 0;
  for (int j = 0; j <= i; j++)
    sum[i][j + 1] = (sum[i][j] + solve(i, j)) % mod;
}
int get(int i, int l, int r)
{
  return (sum[i][r + 1] - sum[i][l] + mod) % mod;
}
int solve(int i, int j)
{
  if (i == s.size())
    return 1;
  if (dp[i][j] != -1)
    return dp[i][j];
  int nums = i + 1, ans = 0;
  solve2(i + 1);
  if (s[i] == '>')
    ans = get(i + 1, 0, min(nums, j));
  else
    ans = get(i + 1, j + 1, nums);
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> s;
  memset(dp, -1, sizeof(dp));
  memset(sum, -1, sizeof(sum));
  cout << solve(0, 0) << endl;
}
// dado uma string s de tamanho n - 1 e um inteiro n
// conte quantas permutacoes de tamanho n satisfazem as seguintes restricoes
// se s[i] == '>', logo p[i] > p[i + 1]
// ou se s[i] == '<', logo p[i] < p[i + 1]

// se eu calculei dp[i][j]
// significa que eu preenchei o prefixo de tamanho i com uma permutacao
// e o ultimo elemento que eu coloquei foi o j (note que j <= i)

// se o proximo elemento precisa ser > j
// entao dp[i][j] = dp[i + 1][j + 1] + ... dp[i + 1][i + 1]
// caso contrario

// note que essa dp eh correta pq
// se eu tou botando um elemento x < n na transicao
// pro prefixo que eu tinha resolvido, posso incrementar todo mundo que for >= x que ta tudo certo
// tipo se eu tinha construido a permutacao 2 1 4 3
// tou calculando dp[4][3] entao pq o 3 foi o ultimo elemento
// mas na transicao tou considerando dp[4][3] = ... dp[5][2] ...
// a permutacao do dp[5][2] seria a 3 1 5 4 2 que continua sendo valida

// soh codar com soma de prefixo pra otimizar a dp e dale nessa questao