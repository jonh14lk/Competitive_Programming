#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

int v[MAXN];

namespace bit
{
  ordered_set<int> bit[MAXN];

  int query(int r, int a, int b)
  {
    int ret = 0, curr = r;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += (bit[r].order_of_key(b + 1) - bit[r].order_of_key(a));
    return ret;
  }
  void add(int idx, int delta)
  {
    for (; idx < MAXN; idx = idx | (idx + 1))
      bit[idx].insert(delta);
  }
  void rem(int idx, int delta)
  {
    for (; idx < MAXN; idx = idx | (idx + 1))
      bit[idx].erase(delta);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// ideia da merge sort tree na bit (fica mais rapido)
// so fazer uma bit de merge sort tree ou vector(se nao tiver update)
// add -> adiciona o numero delta na posição idx
// rem -> remove o numero delta na posição idx
// query -> retorna o numero de elementos tal que posição <= r && (a <= num <= b)
