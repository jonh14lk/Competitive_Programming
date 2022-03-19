#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

vector<int> d1;
vector<int> d2;

void manacher(string s)
{
  d1.resize(s.size());
  d2.resize(s.size());
  int l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
    while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k])
      k++;
    d1[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k, r = i + k;
  }
  l = 0, r = -1;
  for (int i = 0; i < s.size(); i++)
  {
    int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
    while (0 <= i - k - 1 && i + k < s.size() && s[i - k - 1] == s[i + k])
      k++;
    d2[i] = k;
    k = k - 1;
    if (i + k > r)
      l = i - k - 1, r = i + k;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  manacher(s);
  return 0;
}

// algoritimo de manacher

// motivacao: dada uma string s, encontre todos os pares (l, r) tal que, a substring s[l,r]
// e palindroma.

// para cada posicao (0 <= i < s.size()), vamos encontrar os valores de d1[i] e d2[i],
// sendo estes o numero de palindromos com comprimentos impares e com comprimentos pares
// e com i sendo a posicao central desses palindromos

// algoritimo mais facil:
// para cada posicao (0 <= i < s.size()), ele tenta aumentar a resposta em 1
// ate q nao seja mais possivel
// while(s[i - curr] == s[i + curr])
// complexidade O(N^2)

// algoritimo de manacher:
// para cada posicao (0 <= i < s.size()):
// seja o par (l, r) os extremos da substring palindroma que possui o maior r entre todas as encontradas ate entao
// se i > r, o fim do ultimo palindromo foi antes de i: iremos rodar o algoritimo mais facil mais facil e ir ate o limite.
// caso contrario, so precisamos rodar o algoritimo a partir de onde nao foi percorrido previamente.
// ao final se o r atual e maior do que o nosso antigo r, atualizamos o par (l, r)
// por incrivel que pareca, a complexidade e O(N)

// voltando para a motivacao:
// se temos os valores de d1[i] e d2[i]:
// a substring s[i - k, i + k] e palindroma, para todo (0 <= k < d1[i])
// a substring s[i - k - 1, i + k] e palindroma, para todo (0 <= k < d2[i])
// dai temos todos os intervalos
// note que a complexidade do algoritimo de manacher e O(N),
// mas como a quantidade maxima de palindromos em uma string e n^2,
// imprimir todos os intervalos consequentemente teria complexidade O(N^2) no pior caso
