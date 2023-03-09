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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 300005
#define mod 1000000007

int modpow(int a, int b)
{
  int res = 1;
  while (b > 0)
  {
    if (b & 1)
      res = (res * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return res;
}

int all, qt;
int dp[33];

void add(int x)
{
  all++;
  for (int i = 32; i >= 0; i--)
  {
    if (x & (1ll << i))
    {
      if (dp[i] == 0)
      {
        dp[i] = x;
        qt++;
        return;
      }
      x ^= dp[i];
    }
  }
}
int get(int x) // qual o x-esimo menor valor de xor de uma subsequencia
{
  int tot = (1ll << qt), ans = 0;
  for (int i = 32; i >= 0; i--)
  {
    if (dp[i] > 0)
    {
      int d = tot / 2;
      if (d < x && !(ans & (1ll << i)))
        ans ^= dp[i];
      else if (d >= x && (ans & (1ll << i)))
        ans ^= dp[i];
      if (d < x)
        x -= d;
      tot /= 2;
    }
  }
  return ans;
}
bool check(int x) // se existe pelo menos uma subsequencia com xor x
{
  for (int i = 32; i >= 0; i--)
  {
    if (x & (1ll << i))
    {
      if (!dp[i])
        return 0;
      x ^= dp[i];
    }
  }
  return 1;
}
int count(int x) // quantas subsequencias tem xor x
{
  if (!check(x))
    return 0;
  return modpow(2, all - qt);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    add(v[i]);
  }
  int x = get(1ll << qt); // maior xor possivel de uma subsequencia
  int y = get(1);         // maior xor possivel != 0 (o 0 sempre eh possivel - subsequencia vazia)
  return 0;
}
// referencia:
// https://codeforces.com/blog/entry/68953

// problemas:
// https://codeforces.com/gym/103708/problem/A
// https://codeforces.com/contest/959/problem/F
// https://codeforces.com/contest/1101/problem/G
// https://atcoder.jp/contests/abc283/tasks/abc283_g
