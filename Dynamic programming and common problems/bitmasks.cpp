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
#define MAXN 200005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, mask;

  // para printar o valor do bit i
  for (int i = 0; i < n; i++)
    cout << ((mask >> i) & 1) << " ";
  cout << endl;

  // quando eh necessario percorrer todas as submasks ate (1 << n)
  // e fazer algo com todas as submasks dessa mask
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < (1 << n); j++)
    {
      if ((j >> i & 1) == 0)
      {
        //alguma coisa aqui sabendo que a mask(j) eh uma submask de(j ^ 1 << i)
      }
    }
  }

  // para percorrer por todas as submasks de uma mask
  for (int s = mask; s; s = (s - 1) & mask)
  {
    // alguma coisa aqui sabendo que s eh uma submask de mask
  }

  // quando eh necessario percorrer todas as submasks ate (1 << n)
  // e fazer algo com todas as submasks dessa mask O(3^n)
  for (int m = 0; m < (1 << n); m++)
  {
    for (int s = m; s; s = (s - 1) & m)
    {
      // alguma coisa aqui sabendo que mask s eh uma submask de m
    }
  }
  return 0;
}