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
#define MAXN 200005
#define mod 998244353

struct fenw
{
  int n;
  vector<int> bit;
  fenw() {}
  fenw(int sz)
  {
    n = sz;
    bit.assign(sz + 1, 0);
  }
  int qry(int r) // query de prefixo a[0] + a[1] + ...  a[r]
  {
    int ret = 0;
    for (int i = r + 1; i > 0; i -= i & -i)
      ret += bit[i];
    return ret;
  }
  void upd(int r, int x) // a[r] += x
  {
    for (int i = r + 1; i <= n; i += i & -i)
      bit[i] += x;
  }
  int bs(int x) // retorna o maior indice i (i < n) tal que: qry(i) < x
  {
    int i = 0, k = 0;
    while (1 << (k + 1) <= n)
      k++;
    while (k >= 0)
    {
      int nxt_i = i + (1 << k);
      if (nxt_i <= n && bit[nxt_i] < x)
      {
        i = nxt_i;
        x -= bit[i];
      }
      k--;
    }
    return i - 1;
  }
};
