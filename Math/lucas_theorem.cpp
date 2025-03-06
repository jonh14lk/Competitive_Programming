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
#define MAXN 1000006
#define mod 2

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
      if (((n - 1) & i) == i)
        cout << k << " ";
      else
        cout << 0 << " ";
    }
    cout << endl;
  }
}
// https://codeforces.com/contest/2072/problem/F
// problema interessante de um div3, calcular ncr(n, k) mod 2
// ncr(n - 1, i) mod 2 = (((n - 1) & i) == i)

// sejam m e n numeros inteiros nao negativos e p um numero primo
// desenvolver n e m na base p
// ou seja:
// m = m[k]*p^(k) + m[k - 1]*p^(k - 1) + ... + m[0]*p^(0)
// n = n[k]*p^(k) + n[k - 1]*p^(k - 1) + ... + n[0]*p^(0)

// então:
// ncr(m, n) mod p = produtorio de (ncr(m[i], n[i]) mod p)

// dai pra generalizar pro mod 2 eh deboas, pq se tiver um bit setado em n[i] que nao ta setado em m[i], entao miou, vai dar zero