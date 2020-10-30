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
#define DEBUG 0
#define MAXN 5001
#define mod 1000000009 // modulo
#define d 31           // uma boa escolha para a base da potencia

vector<int> v;
vector<int> pot;
vector<int> hashing;

void calc(int n)
{
  int curr = 1;
  pot.pb(curr);
  for (int i = 1; i <= n; i++)
  {
    curr = (curr * d) % mod;
    pot.pb(curr);
  }
}
void prefix_hash()
{
  int curr = 0;
  for (int i = 0; i < v.size(); i++)
  {
    int val = (v[i] * pot[i]) % mod;
    curr = (curr + val) % mod;
    hashing.pb(curr);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  for (auto const &i : s)
    v.pb((i - 'a') + 1);                 // indexar a partir do 1
  calc(v.size());                        // potencias de d
  prefix_hash();                         // hashing dos prefixos de s
  cout << hashing[v.size() - 1] << endl; // resposta final
  return 0;
}
// string hashing
// podemos representar uma string como um valor inteiro
// seja s uma string e d o tamanho do alfabeto
// o valor de hashing de s eh igual a:
// (s[0] * pow(d, 0)) + (s[1] * pow(d, 1)) + ... (s[n - 1] * pow(d, n - 1))
// como esse valor pode ser gigantesco
// fazer isso com um modulo que for o maior possivel
// nesse caso usaremos 10^9 + 7
// logo o hashing fica:
// ((s[0] * pow(d, 0)) + (s[1] * pow(d, 1)) + ... (s[n - 1] * pow(d, n - 1))) % mod
// o hashing possui diversas aplicacoes como:
// checar substring que sao palindromas
// numeros de substrings diferentes em uma string
// etc...
