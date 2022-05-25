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
#define MAXN 100005
#define mod 1000000007

struct modint
{
  int val;
  modint(int v = 0) { val = v % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z = z * x;
      x = x * x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

modint ncr(int n, int k)
{
  // calcular combinacao para n grande
  // nesse problema n <= 10^12
  // em O(k)
  modint num = 1;
  modint den = 1;
  for (int i = 0; i < k; i++)
  {
    num = num * modint(n - i);
    den = den * modint(i + 1);
  }
  modint ans = num / den;
  return ans;
}
modint stars_and_bars(int n, int k)
{
  // para pares de inteiros n e k
  // enconte a quantidade de k-tuplas com soma == n
  // x1 + x2 + ... + xk = n
  return ncr(n + k - 1, k - 1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, s;
  cin >> n >> s;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  modint all = stars_and_bars(s, n);
  modint to_sub = 0;
  for (int mask = 1; mask < (1 << n); mask++)
  {
    int sum = 0;
    for (int j = 0; j < n; j++)
    {
      if (mask & (1 << j))
        sum += (v[j] + 1);
    }
    if (sum <= s)
    {
      modint curr = stars_and_bars(s - sum, n);
      to_sub = (__builtin_popcount(mask) % 2) ? to_sub + curr : to_sub - curr;
    }
  }
  all = all - to_sub;
  cout << all.val << endl;
  return 0;
}
// stars and bars
// dado dois inteiros positivos n e k
// conte o numero de k-tuplas (x1, x2, .., xk) tal que
// x1 + x2 + ... + xk = n
// com x1, x2, ..., xk >= 0
// resposta = ncr(n + k - 1, k - 1)

// para k-tuplas com x1, x2, ..., xk > 0:
// resposta = ncr(n - 1, k - 1)

// problema exemplo:
// https://codeforces.com/contest/451/problem/E
// contar quantas k-tuplas com soma == n
// tal que: x[i] >= 0 e x[i] <= f[i]
// k <= 20

// solucao:
// conta tudo com stars and bars
// dai preciso subtrair todas as possibilidades invalidas (com pelo menos um i tal que x[i] > f[i])
// seja n(i) as possibilidades com x[i] > f[i]
// dai eu quero calcular a quantidade de elementos na uniao entre todos os n(i)
// dai da pra fzr usando a formulinha de uniao de conjuntos:
// n(A uniao B uniao C) = n(A) + n(B) + n(C) - n(A intersecao B) ... + n(A intersecao B intersecao C)
// itera por todos os 2^n subsets e calcula o que deve subtrair/somar com aqueles caras