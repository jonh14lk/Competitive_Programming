
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 11

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int bits = 0;
  while (n)
  {
    if (n & 1)
      bits++;
    n = n >> 1;
  }
  int ans = pow(2, bits);
  cout << ans << endl;
  return 0;
}
// resposta = quantidade de elementos impares em uma linha do triangulo de pascal
// teorema = quantidade de bits setados em n ao quadrado é igual a resposta