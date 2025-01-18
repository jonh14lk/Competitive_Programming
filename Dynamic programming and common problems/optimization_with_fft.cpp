#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct modint
{
  int val;
  modint(int v = 0) { val = ((v % mod) + mod) % mod; }
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
  int operator*(modint o) { return ((val * 1ll * o.val) % mod); }
  int operator/(modint o) { return (val * 1ll * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};
namespace fft
{
  int n;
  int root = -31;
  int root_1 = 128805723;
  int pw = __builtin_ctz(mod - 1);
  int root_pw = (1 << pw);

  void ntt(vector<modint> &a, bool invert)
  {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++)
    {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1)
        j ^= bit;
      j ^= bit;
      if (i < j)
        swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1)
    {
      modint wlen = (invert) ? root_1 : root;
      for (int i = len; i < root_pw; i <<= 1)
        wlen *= wlen;
      for (int i = 0; i < n; i += len)
      {
        modint w = 1;
        for (int j = 0; j < len / 2; j++)
        {
          modint u = a[i + j];
          modint v = a[i + j + len / 2] * w;
          a[i + j] = u + v;
          a[i + j + len / 2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert)
    {
      modint n_1 = modint(n).inv();
      for (int i = 0; i < a.size(); i++)
        a[i] *= n_1;
    }
  }
  vector<modint> mul(vector<modint> &a, vector<modint> &b)
  {
    n = 1;
    while (n < 2 * max(a.size(), b.size()))
      n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++)
      a[i] *= b[i];
    ntt(a, true);
    return a;
  }
}

// int dp[3005][3005 + 3005];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // dp naive:
  // auto get = [&](int i, int j)
  // {
  //   return dp[i][j + 3005];
  // };
  // dp[1][3005] = 1;
  // for (int i = 2; i < 3005; i++)
  // {
  //   for (int j = -i; j <= i; j++)
  //   {
  //     dp[i][j + 3005] = get(i - 1, j - 1);
  //     dp[i][j + 3005] += get(i - 1, j + 1);
  //     dp[i][j + 3005] += (i - 2) * get(i - 1, j);
  //     dp[i][j + 3005] %= mod;
  //   }
  // }
  // for (int i = 0; i <= 5; i++)
  // {
  //   for (int j = -i; j <= i; j++)
  //     cout << dp[i][j + 3005] << ", ";
  //   cout << endl;
  // }
  int n, k;
  cin >> n >> k;
  queue<vector<modint>> vecs;
  vecs.push({0, 1, 0}); // dp[1][-1], dp[1][0], dp[1][1]
  for (int i = 2; i <= n; i++)
  {
    // dp[i] = fft::conv(dp[i - 1], {1, i - 2, 1})
    vecs.push({1, i - 2, 1});
  }
  // faz as convolucoes pegando smp os dois de menor tamanho
  while (vecs.size() > 1)
  {
    vector<modint> v = vecs.front();
    vecs.pop();
    vector<modint> v2 = vecs.front();
    vecs.pop();
    vector<modint> v3 = fft::mul(v, v2);
    vecs.push(v3);
  }
  // quero o valor de dp[n][k], o k dado na entrada pode ser negativo
  cout << vecs.back()[k + n].val << endl;
}
// https://atcoder.jp/contests/abc385/tasks/abc385_g
// a dp eh tipo:
// dp[i][j] = dp[i - 1][j] * (i - 2) + dp[i - 1][j - 1] + dp[i - 1][j + 1]
// considerando um certo i, j ta no intervalo [-i, i]
// mas n eh na casa de 10ˆ5