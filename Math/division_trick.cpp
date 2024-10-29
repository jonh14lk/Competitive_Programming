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

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  auto soma_pa = [&](int l, int r)
  {
    int x = (l + r) % mod;
    x = (x * ((r - l + 1) % mod)) % mod;
    x = (x * 500000004) % mod; // divisao por 2
    return x;
  };
  int ans = 0;
  for (int l = 1, r; l <= n; l = r + 1)
  {
    // todos os numeros i no intervalo [l, r] possuem (n / i) == x
    r = n / (n / l);
    int x = (n / l);
    // for (int i = l; i <= r; i++)
    //   assert((n / i) == x);
    ans += (x * soma_pa(l, r));
    ans %= mod;
  }
  cout << ans << endl;
}
// https://cses.fi/problemset/task/1082
// dado um n, ache a soma dos divisores de todos os numeros de 1 ate n, (n <= 10ˆ12)
// se a gnt computar a contribuicao de cada divisor na resposta
// isso fica: achar a soma de i * floor(n / i) para todos os numeros de 1 ate n
// a quatidade de valores distintos de floor(n / i) eh O(sqrt(n))
// entao o que queremos eh iterar por todos os valores possiveis, e ver o intervalo de numeros
// que tem o valor de floor(n / i) sendo um determinado x
