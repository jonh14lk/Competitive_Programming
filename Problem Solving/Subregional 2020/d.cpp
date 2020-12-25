#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 1
#define MAXN 201

int n, m, k;
vector<pi> answer;
vector<int> da;
vector<int> db;

namespace rk
{
  const int p = 31;
  const int mod = 1e9 + 9;

  int multiplicate(int x, int y)
  {
    return (x * y) % mod;
  }
  int subtract(int a, int b)
  {
    return (a - b < 0) ? a - b + mod : a - b;
  }
  int sum(int a, int b)
  {
    return (a + b >= mod) ? a + b - mod : a + b;
  }
  void rabin_karp()
  {
    int n = da.size(), m = db.size();
    vector<int> pot(n);
    pot[0] = 1;
    for (int i = 1; i < n; i++)
      pot[i] = multiplicate(pot[i - 1], p);
    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
      int val = multiplicate(pref[i], p);
      pref[i + 1] = sum(da[i], val);
    }
    int hs = 0;
    for (int i = 0; i < m; i++)
    {
      int val = multiplicate(hs, p);
      hs = sum(db[i], val);
    }
    for (int i = 0; i + m - 1 < n; i++)
    {
      int cur_h = subtract(pref[i + m], multiplicate(pref[i], pot[m]));
      if (cur_h == hs)
        answer.pb({i, i + m - 1});
    }
  }
}
namespace get_ans
{
  const int mod = 1e9 + 7;
  vector<vector<int>> ans(2, vector<int>(2));

  vector<vector<int>> multiply(vector<vector<int>> a, vector<vector<int>> b)
  {
    vector<vector<int>> res(2, vector<int>(2));
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
      {
        res[i][j] = 0;
        for (int k = 0; k < 2; k++)
          res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % mod) % mod;
      }
    }
    return res;
  }
  vector<vector<int>> expo(vector<vector<int>> mat, int m)
  {
    for (int i = 0; i < 2; i++)
      for (int j = 0; j < 2; j++)
        ans[i][j] = (i == j);
    while (m)
    {
      if (m & 1)
        ans = multiply(ans, mat);
      m = m / 2;
      mat = multiply(mat, mat);
    }
    return ans;
  }
  int solve(int i, int j)
  {
    vector<vector<int>> kappa = {{0}, {1}};
    vector<vector<int>> bas = {{0, n - 1}, {1, n - 2}};
    bas = expo(bas, i);
    return (!j) ? ans[0][0] : ans[1][0];
  }
  void resp()
  {
    int gg = 0, aa = -1, bb = -1;
    for (auto const &i : answer)
    {
      if (!i.fir)
      {
        if (aa == -1)
          aa = solve(k, 0);
        gg = (gg + aa) % mod;
      }
      else
      {
        if (bb == -1)
          bb = solve(k, 1);
        gg = (gg + bb) % mod;
      }
    }
    cout << gg << endl;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int i = 0; i < n; i++)
    cin >> b[i];
  for (int i = 0; i < n - 1; i++)
    a.pb(a[i]);
  for (int i = 0; i < a.size() - 1; i++)
  {
    int num = a[i + 1] - a[i];
    num = ((num % m) + m) % m;
    da.pb(num);
  }
  for (int i = 0; i < b.size() - 1; i++)
  {
    int num = (b[i + 1] - b[i]) * -1;
    num = ((num % m) + m) % m;
    db.pb(num);
  }
  rk::rabin_karp();
  get_ans::resp();
  return 0;
}
// Condição:
// (a[0] + b[0]) % m = (a[1] + b[1]) % m = ... = (a[n] + b[n]) % m
// A GRANDE SACADA para que a condição seja valida:
// (a[i] - a[i - 1]) mod m = ((b[i] - b[i - 1]) * -1) mod m
// ou seja, o proximo b[i] vai ter que decrescer a mesma
// quantia que o proximo a[i] cresceu
// sabendo disso, quantas rotações satisfazem a condição?
// e de quantos jeitos podemos chegar nessa rotação?
// da[i] = (a[i + 1] - a[i])
// db[i] = (b[i + 1] - b[i]) * -1
// isso cada da[i] e db[i] sempre mod m
// o matching vai ser sempre um shift de a com b
// com isso podemos fazer uma copia do array da e jogar no final
// e usar algum algoritimo de matching de string para ver os shifts válidos
// dai temos a quantidade de rotações que satisfazem a condição
// agora, para cada uma dessas rotações, vamos calcular de quantos jeitos podemos chegar
// em cada uma delas
// ans = jeitos(x1) + jeitos(x2) + ... + jeitos(xn)
// jeitos(xi) = quantidade(p0 + p1 + ... + pk = xi mod m)
// f(x, 0) -> terminar apos x movimentos na configuração inicial
// f(x, 1) -> terminar apos x movimentos na configuração sem ser a inicial
// f(x, 0) = (n - 1) * f(x - 1, 1)
// f(x, 1) = f(x - 1, 0) + (n - 2) * f(x - 1 , 1)
// com isso, temos dois casos:
// 1- a configuração inicial é valida: ans += f(k, 0)
// 2- uma configuração que não é a inicial é válida: ans += f(k, 1)
// com isso, da pra fazer com exponenciação de matrizes
// e temos a resposta :)
