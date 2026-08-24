#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

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
modint inv[MAXN];
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
  if (k > n)
    return 0;
  modint ans = f[n] * invfat[k];
  ans *= invfat[n - k];
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  int n, k;
  cin >> n >> k;
  map<int, int> mp;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    mp[x]++;
  }
  map<int, int> cnt;
  for (auto const &i : mp)
  {
    cnt[i.sec]++;
  }
  vector<pi> vec;
  for (auto const &i : cnt)
  {
    vec.pb({i.fir, i.sec});
  }
  modint ans = 0;
  for (int j = 0; j <= k; j++)
  {
    modint tot = ncr(k, j); // qtd de subsets de comissoes de tamanho j
    modint prod = tot;
    for (auto [x, qt] : vec)
    {
      modint term = ncr(j, x); // escolher x comissoes distintas entre as j consideradas na inc-exc
      term *= f[x];            // cada cara eh alocado pra uma comissao, cada cara eh considerado como diferente
      term = term.pow(qt);
      prod *= term;
    }
    ans = ((k - j) % 2) ? ans - prod : ans + prod;
  }
  ans /= f[k];
  cout << ans.val << endl;
  return 0;
}
