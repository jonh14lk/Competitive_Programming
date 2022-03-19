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
#define MAXN 100001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // exemplos de sos dp para calcular f[x] para cada mask x
  // a[x] eh o valor de uma funcao a para uma mask x
  // complexidade: O(M * 2^M), M = numero de bits

  // Exemplo 1:
  // nesse caso, f[x] eh a funcao que soma:
  // todos os a[i], tal que, (x & i) == i)
  // isso eh, i eh uma "mask filha" de x
  // pois todos os bits de i estao setados em x
  for (int mask = 0; mask < (1 << m); mask++)
  {
    f[mask] = a[mask];
  }
  for (int i = 0; i < m; ++i)
  {
    for (int mask = 0; mask < (1 << m); mask++)
    {
      if (mask & (1 << i))
        f[mask] += f[mask ^ (1 << i)];
    }
  }

  // Exemplo 2:
  // nesse caso, f[x] eh a funcao que soma:
  // todos os a[i], tal que, (x & i) == x)
  // isso eh, i eh uma "mask pai" de x
  // pois todos os bits de x estao setados em i
  for (int mask = 0; mask < (1 << m); mask++)
  {
    f[mask] = a[mask];
  }
  for (int i = 0; i < m; ++i)
  {
    for (int mask = 0; mask < (1 << m); mask++)
    {
      if (!(mask & (1 << i)))
        f[mask] += f[mask ^ (1 << i)];
    }
  }

  return 0;
}
// https://codeforces.com/blog/entry/45223
