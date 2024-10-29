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

struct modint
{
  int val;
  modint(int v = 0) { val = v % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

modint f[MAXN];
modint invfat[MAXN];

void calc()
{
  f[0] = 1;
  invfat[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    f[i] = f[i - 1] * i;
    invfat[i] = f[i].inv();
  }
}
modint ncr(int n, int k) // combinacao
{
  modint ans = f[n] * invfat[k];
  ans *= invfat[n - k];
  return ans;
}
modint arr(int n, int k) // arranjo
{
  modint ans = f[n] * invfat[n - k];
  return ans;
}

int h, w, n;
pi v[3005];
modint m1 = 1000000006; // -1
modint dp[3005][3005][2];
bool vis[3005][3005][2];

modint solve(int i, int j, int par)
{
  if (i > n)
  {
    modint ans = ncr((h - v[j].fir) + (w - v[j].sec), h - v[j].fir);
    if (!par)
      return ans;
    return ans * m1;
  }
  if (vis[i][j][par])
  {
    return dp[i][j][par];
  }
  modint ans = solve(i + 1, j, par);
  if (v[i].sec >= v[j].sec)
  {
    modint nxt = solve(i + 1, i, (par + 1) % 2);
    modint curr = ncr((v[i].fir - v[j].fir) + (v[i].sec - v[j].sec), v[i].fir - v[j].fir);
    curr *= nxt;
    ans = ans + curr;
  }
  vis[i][j][par] = 1;
  dp[i][j][par] = ans;
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  cin >> h >> w >> n;
  // tenho que fazer essa inclusao exclusao numa dp
  // for (int i = 0; i < n; i++)
  //   cin >> v[i].fir >> v[i].sec;
  // sort(v, v + n);
  // modint ans = 0;
  // for (int mask = 0; mask < (1 << n); mask++)
  // {
  //   modint at = 1;
  //   pi prv = {1, 1};
  //   for (int j = 0; j < n; j++)
  //   {
  //     if (mask & (1 << j))
  //     {
  //       if (v[j].sec < prv.sec)
  //       {
  //         at = 0;
  //         break;
  //       }
  //       at *= ncr((v[j].fir - prv.fir) + (v[j].sec - prv.sec), v[j].fir - prv.fir);
  //       prv = v[j];
  //     }
  //   }
  //   at *= ncr((h - prv.fir) + (w - prv.sec), h - prv.fir);
  //   cout << mask << " " << at.val << endl;
  //   ans = (__builtin_popcount(mask) % 2) ? ans - at : ans + at;
  // }
  // cout << ans.val << endl;
  v[0] = {1, 1};
  for (int i = 1; i <= n; i++)
    cin >> v[i].fir >> v[i].sec;
  sort(v, v + n + 1);
  cout << solve(1, 0, 0).val << endl;
}
// https://atcoder.jp/contests/dp/tasks/dp_y
// dado um grid com h linhas e w colunas
// h, w <= 10ˆ5
// existem n <= 3000 posicoes com wall

// quantos caminhos tem do square (1, 1) ate o (h, w)

// com isso, podemos fzr inclusao exclusao
// calculando quantos caminhos passam por um conjunto de walls
// mas nao podemos fazer 2ˆ30
// maaas, podemos fazer uma dp pra computar essa inclusao exclusao
// e dale