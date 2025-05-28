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
#define pii pair<pi, int>
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

int freq[MAXN];
int mp[MAXN];
vector<int> d[MAXN];
vector<int> prime_divs[MAXN];
modint pot[MAXN];
modint to_upd[MAXN];
modint res[MAXN];
bitset<MAXN> prime;

void calc()
{
  pot[0] = 1;
  for (int i = 1; i < MAXN; i++) // potencias de 2
  {
    pot[i] = pot[i - 1] * 2;
  }
  prime.set();
  prime[0] = false;
  prime[1] = false;
  for (int i = 2; i < MAXN; i++) // primos
  {
    if (prime[i])
      for (int j = 2; j * i < MAXN; j++)
        prime[j * i] = false;
  }
  for (int i = 1; i < MAXN; i++) // divisores
  {
    for (int j = i; j < MAXN; j += i)
    {
      d[j].pb(i);
      if (prime[i])
        prime_divs[j].pb(i);
    }
  }
}
void add(int x, int val)
{
  for (auto const &d : d[x])
  {
    if (val == 1)
    {
      to_upd[d] = pot[mp[d]];
      mp[d]++;
    }
    else
    {
      mp[d]--;
      to_upd[d] = ((pot[mp[d]] * -1) + mod) % mod;
    }
  }
  for (auto const &p : prime_divs[x])
  {
    for (auto const &d : d[x])
    {
      if ((d * p) > x)
        break;
      to_upd[d] -= to_upd[d * p];
    }
  }
  for (auto const &d : d[x])
  {
    res[d] += to_upd[d];
    to_upd[d] = 0;
  }
}
void prec()
{
  for (int i = 1; i < MAXN; i++)
  {
    mp[i] = 0;
    for (int j = i; j < MAXN; j += i)
      mp[i] += freq[j];
    res[i] = pot[mp[i]] - 1;
  }
  for (int p = 1; p < MAXN; p++)
  {
    if (prime[p])
    {
      for (int x = 1; x * p < MAXN; x++)
        res[x] -= res[x * p];
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  calc();
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    freq[v[i]]++;
  }
  prec();
  int q;
  cin >> q;
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int x;
      cin >> x;
      modint tot = pot[n] - 1;
      modint ans = res[x] / tot;
      cout << ans.val << "\n";
    }
    else
    {
      int j, x;
      cin >> j >> x;
      j--; // 1 indexado
      add(v[j], -1);
      v[j] = x;
      add(v[j], 1);
    }
  }
  return 0;
}
// 562 ms no cf