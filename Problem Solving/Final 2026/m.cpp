#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

vector<pi> dale;
int dp[MAXN][2];

int solve(int i, int j)
{
  if (i == dale.size())
    return (j == 0) ? 0 : 1e18;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ans = 1e18;
  ans = min(ans, solve(i + 1, 0) - dale[i].sec);
  ans = min(ans, solve(i + 1, 1));
  if (j == 0)
    ans += dale[i].fir;
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s, t;
  cin >> s >> t;
  reverse(s.begin(), s.end());
  reverse(t.begin(), t.end());
  vector<int> v, v2;
  int cnt = 0;
  for (auto const &i : s)
  {
    if (i == 'D')
      cnt++;
    else
      v.pb(cnt);
  }
  cnt = 0;
  for (auto const &i : t)
  {
    if (i == 'D')
      cnt++;
    else
      v2.pb(cnt);
  }
  reverse(v.begin(), v.end());
  reverse(v2.begin(), v2.end());
  vector<pair<pi, pi>> inter;
  {
    int l = 0;
    while (l < v.size())
    {
      int r = l;
      while (r + 1 < v.size() && v[r + 1] == v[l])
        r++;
      inter.pb({{l, r}, {v[l], 0}});
      l = r + 1;
    }
  }
  {
    int l = 0;
    while (l < v2.size())
    {
      int r = l;
      while (r + 1 < v2.size() && v2[r + 1] == v2[l])
        r++;
      inter.pb({{l, r}, {v2[l], 1}});
      l = r + 1;
    }
  }
  sort(inter.begin(), inter.end());
  vector<int> mx(2, -1);
  vector<int> min_val(2, 1e18);
  vector<int> max_val(2, -1);
  for (auto const &i : inter)
  {
    auto [l, r] = i.fir;
    auto [val, id] = i.sec;
    mx[id] = r;
    min_val[id] = min(min_val[id], val);
    max_val[id] = max(max_val[id], val);
    if (mx[0] == mx[1])
    {
      int to_eq = max(max_val[0], max_val[1]);
      dale.pb({2 * max(max_val[0], max_val[1]), min_val[0] + min_val[1]});
      min_val.assign(2, 1e18);
      max_val.assign(2, -1);
    }
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0, 0) << endl;
  return 0;
}
// a quantidade de u e de d sao iguais
// nenhum prefixo tem mais d do que u, isso garante que s[0] e t[0] sao iguais a u
// se eu defino, quantos u tem a minha frente e monto um array
// a operacao eh, selecione um bloco maximal de caras iguais em um dos arrays
// e incremente eles em 1
// uma vez que a[i] == a[i + 1], eles nunca mais passam a ser diferentes
// alem disso a sempre vai ser nao crescente, independente do que aconteca
// pro primeiro sample temos
// 3 3 1 e 3 3 3
// separar cada array em blocos de caras iguais e ir igualando eles
// entao meio que vc vai sempre incrementando blocos do menor pro maior em um dos arrays
// e dependendo do quanto vc incrementou esse bloco menor, ele deu join com outro bloco
