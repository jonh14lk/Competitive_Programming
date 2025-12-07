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

int moddiv(int x, int y)
{
  x %= mod;
  y %= mod;
  auto modpow = [&](int a, int b)
  {
    int z = 1;
    while (b)
    {
      if (b & 1)
        z = (z * a) % mod;
      a = (a * a) % mod;
      b >>= 1;
    }
    return z;
  };
  return (x * modpow(y, mod - 2)) % mod;
};
int bsgs(int a, int b, int m)
{
  if (m == 1)
    return 0;
  a %= m, b %= m;
  int n = sqrt(m) + 1;
  int an = 1;
  for (int i = 0; i < n; i++)
  {
    an = (an * a) % m;
  }
  unordered_map<int, int> vals;
  for (int q = 0, cur = b; q < n; ++q)
  {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }
  for (int p = 1, cur = 1; p <= n; ++p)
  {
    cur = (cur * an) % m;
    if (vals.count(cur))
    {
      int ans = n * p - vals[cur];
      return ans;
    }
  }
  return -1;
}
void naive(int n, vector<int> &v)
{
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int curr = to_string(v[i] / v[j]).size(); // parte inteira
      int g = __gcd(v[i], v[j]);
      int y = v[j] / g;
      int a = 0, b = 0;
      while (y % 2 == 0)
      {
        a++;
        y /= 2;
      }
      while (y % 5 == 0)
      {
        b++;
        y /= 5;
      }
      curr += max(a, b);      // antiperiodo
      curr += bsgs(10, 1, y); // periodo
      ans += curr;
    }
  }
  cout << moddiv(ans, (n * n)) << endl;
}
int solve1(int n, vector<int> &v) // parte inteira
{
  auto f = [&](int x, int y)
  {
    return to_string(v[x] / v[y]).size();
  };
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    int j = 0;
    while (j < n)
    {
      int l = j, r = n - 1;
      int curr = f(i, j);
      while (l < r)
      {
        int mid = (l + r + 1) >> 1;
        (f(i, mid) == curr) ? l = mid : r = mid - 1;
      }
      ans += (l - j + 1) * curr;
      j = l + 1;
    }
  }
  return ans;
}
int solve2(int n, vector<int> &v) // parte decimal
{
  vector<vector<int>> divs(MAXN);
  for (int i = 1; i < MAXN; i++)
  {
    for (int j = i; j < MAXN; j += i)
      divs[j].pb(i);
  }
  for (int i = 1; i < MAXN; i++)
  {
    reverse(divs[i].begin(), divs[i].end());
  }
  vector<int> antiperiod(MAXN);
  vector<int> period(MAXN);
  for (int i = 1; i < MAXN; i++)
  {
    int y = i;
    int a = 0, b = 0;
    while (y % 2 == 0)
    {
      a++;
      y /= 2;
    }
    while (y % 5 == 0)
    {
      b++;
      y /= 5;
    }
    antiperiod[i] = max(a, b);
    period[i] = bsgs(10, 1, y);
  }
  vector<int> cnt(MAXN, 0);
  for (auto const &x : v)
  {
    for (auto const &i : divs[x])
      cnt[i]++;
  }
  int ans = 0;
  vector<int> dp(MAXN);
  for (auto const &x : v)
  {
    for (auto const &g : divs[x])
    {
      dp[g] = cnt[g];
    }
    for (auto const &g : divs[x])
    {
      for (auto const &d : divs[g])
      {
        if (d < g)
          dp[d] -= dp[g];
      }
      ans += dp[g] * antiperiod[x / g];
      ans += dp[g] * period[x / g];
    }
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  sort(v.begin(), v.end());
  int ans = solve1(n, v) + solve2(n, v);
  cout << moddiv(ans, (n * n)) << endl;
  return 0;
}