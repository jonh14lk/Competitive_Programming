#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007
#define inf 1e9

struct sqrt_rmq
{
  int n, sq;
  vector<int> a;
  vector<int> block;

  sqrt_rmq(int sz)
  {
    n = sz;
    sq = sqrt(n) + 1;
    a = vector<int>(n, inf);
    block = vector<int>((n + sq - 1) / sq, inf);
  }
  void upd(int i, int x) // O(1)
  {
    int b = i / sq;
    a[i] = min(a[i], x);
    block[b] = min(block[b], x);
    // eh possivel fzr o update em O(sqrt(n)) se necessario (dependendo da operacao)
    // basta computar o valor de block[i / sq] novamente
    // for (int j = b * sq; j < min(n, (b + 1) * sq); j++) block[b] = min(block[b], a[j]);
  }
  int query(int l, int r) // O(sqrt(n))
  {
    int ans = inf;
    for (; l <= r && l % sq; l++)
      ans = min(ans, a[l]);
    for (; (l + sq - 1) <= r; l += sq)
      ans = min(ans, block[l / sq]);
    for (; l <= r; l++)
      ans = min(ans, a[l]);
    return ans;
  }
};
// point update, range query
// util para quando temos muitos updates e poucas queries
// eh facil de adaptar para ser max ao inves de min
// ou ate para ser query de soma se o update for somar x em um a[i]
// problema bom pra usar: https://codeforces.com/gym/106679/problem/G
