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
#define pii pair<pi, int>
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
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

int qtd_2_fact(int n) // legendre formula
{
  int pot = 2, sum = 0;
  for (int i = 1; i <= 60; i++)
  {
    sum += (n / pot);
    pot *= 2;
  }
  return sum;
}
int qtd_2_ncr(int a, int b)
{
  int res = qtd_2_fact(a);
  res -= qtd_2_fact(b);
  res -= qtd_2_fact(a - b);
  return res;
}
int get(int i, int j)
{
  int ncr_qtd_2 = qtd_2_ncr(i + j, j);
  return max(0ll, (i + j) - ncr_qtd_2);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int a, b;
  cin >> a >> b;
  int ans = 0;
  for (int i = a - 1; i >= 0 && (a - i) <= 100; i--)
  {
    for (int j = b - 1; j >= 0 && (b - j) <= 100; j--)
      ans = max(ans, get(i, j));
  }
  modint pot = modint(2).pow(ans + 1);
  cout << pot.val << endl;
  return 0;
}
// n sempre vai ser uma potencia de 2
// se vc fixou algo como i vitorias e j derrotas
// i < a e j < b

// existem (n / 2^(i + j)) * ncr(i + j, i)
// jogadores que chegam nessa configuracao de i vitorias e j derrotas
// pois existem ncr(i + j, i) caminhos distintos para sair de uma posicao (0, 0) e chegar na posicao (i, j)
// quando se pode fazer um move (i, j) -> (i + 1, j) ou (i, j) -> (i, j + 1)
// alem disso, vai ser feitas (i + j) divisoes por 2 ao longo do caminho em todos eles
// uma vez q o caminho chegou em (i, j) logo chegou (n / 2^(i + j)) participantes seguindo exatamente aquele caminho

// note que essa quantidade precisa ser um numero par
// pois como i < a e j < b, logo o jogo ainda nao acabou e um proximo move precisa ser feito
// logo esse numero (n / 2^(i + j)) * ncr(i + j, i) precisa ser par, se for impar
// ai nao tem como para aquele n

// entao meio que o problma vira, qual o expoente minimo ans
// tal que n = 2^ans satisfaz essas restrições ai
// ou seja, vai ter um n = 2^ans
// em que (n / 2^(i + j)) * ncr(i + j, i) eh par
// para todo  0 <= i < a e 0 <= j < b

// se eu fixo um (i, j)
// entao eu posso pegar a quantidade de fatores 2 em ncr(i + j, i)
// e a quantidade de fatores 2 em 2^(i + j), que eh igual a (i + j) ne

// entao o menor n pensando somente nesse (i, j) vai ser:
// n = 2^ans -> ans = max(0, (i + j) - qtd_2(ncr(i + j, i)))
// no qual qtd_2(x) -> quantidade de fatores 2 em x

// mas ai chega no problema de:
// como peste eu acho qtd_2(ncr(i + j, i))) para um dado (i, j)?
// possivelmente essa eh a parte mais dificil da solucao, ou pelo menos q eu n sabia como
// legendre formula!
// com a legendre formula eh possivel achar qtd_2(x), no caso de x = f!
// o que eh suficiente pra achar a quantidade de fatores em um coeficiente binomial

// alem disso, existem muitas possiblidades de pares (i, j) que preciso considerar ne
// visto que a e b vai ate 10^18
// mas pelo visto da pra chutar que se tu pega i >= a - 100 e j >= b - 100 ja eh o suficiente
// O(fé) no chute e eh isso
// a segunda parte mais maluca do problema, pq ou tu prova ou vai na cara de pau do chute msm