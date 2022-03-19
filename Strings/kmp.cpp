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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353
 
string s;
int n, m;
string a, b;
int c[MAXN][26];
 
vector<int> kmp(string &s)
{
  int n = s.size();
  vector<int> p(n);
  for (int i = 1; i < n; i++)
  {
    int j = p[i - 1];
    while (j > 0 && s[i] != s[j])
      j = p[j - 1];
    if (s[i] == s[j])
      j++;
    p[i] = j;
  }
  return p;
}
void compute(string s)
{
  s.pb('*');
  vector<int> p = kmp(s);
  for (int i = 0; i < s.size(); i++)
  {
    for (int cc = 0; cc < 26; cc++)
    {
      int j = i;
      while (j > 0 && 'a' + cc != s[j])
        j = p[j - 1];
      if ('a' + cc == s[j])
        j++;
      c[i][cc] = j;
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  compute(s);
  return 0;
}
// kmp
// algoritmo eh online, vai coonstruindo da esquerda pra direita
// calcula pi[i], a seguinte funcao:
// seja a substring s.substr(0, i + 1)
// pi[i] = tamanho do maior prefixo que tbm eh um sufixo dessa substring

// dai por exemplo
// da pra contar a quantidade de matchings de s em t
// so concatenar as strings fazendo: t = s + "*" + t
// dai contar as posicoes com pi[i] = s.size()

// tambem eh possivel construir um automato do kmp
// do tipo
// se meu pi[i] == x, e leio a letra c
// dai devo ir pro estado p[i] == y
// as transições podem ser computadas e isso pode ser muito util