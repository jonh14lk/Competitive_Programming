#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 210
#define MAXP 1505
#define mod 998244353

int v[MAXN];
vector<int> all_primes;
vector<int> prime_divs[MAXN];
int dp[MAXN][MAXN][MAXP];

int solve(int l, int r, int p)
{
  if (l > r)
    return 0;
  if (l == r)
    return 1;
  if (dp[l][r][p] != -1)
    return dp[l][r][p];
  int ans = 1e18;
  if (p == 0)
  {
    for (auto const &x : prime_divs[l])
      ans = min(ans, solve(l, r, x));
  }
  else
  {
    ans = 1 + solve(l + 1, r, 0);
    for (int mid = l + 1; mid <= r; mid++)
      if (v[mid] % all_primes[p] == 0)
        ans = min(ans, solve(l + 1, mid - 1, 0) + solve(mid, r, p));
  }
  return dp[l][r][p] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int j = 0; j < n; j++)
  {
    cin >> v[j];
    int x = v[j];
    for (int i = 2; (i * i) <= x; i++)
    {
      while (x % i == 0)
      {
        all_primes.pb(i);
        x /= i;
      }
    }
    if (x >= 2)
      all_primes.pb(x);
  }
  all_primes.pb(-1);
  sort(all_primes.begin(), all_primes.end());
  all_primes.erase(unique(all_primes.begin(), all_primes.end()), all_primes.end());
  assert(all_primes.size() < MAXP); // no maximo 7 fatores primos distintos por elemento
  assert(all_primes[0] == -1);
  for (int i = 0; i < n; i++)
  {
    for (int j = 1; j < all_primes.size(); j++)
    {
      if (v[i] % all_primes[j] == 0)
        prime_divs[i].pb(j);
    }
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0, n - 1, 0) << endl;
  return 0;
}