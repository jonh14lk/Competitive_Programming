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
#define mod 1000000007

int n, sum;
int w[MAXN];
bool vis[MAXN];
double dp[MAXN];
int sum_divs[MAXN];
int sum_mul[MAXN];
vector<int> divs[MAXN];

int cnt(int curr, int nxt)
{
  // quero considerar todos os numeros tal que
  // que tem a forma de d * (nxt /curr)
  // no qual d eh um divisor de curr
  int a = nxt / curr;
  int ans = 0;
  for (auto const &i : divs[curr])
  {
    int l = (i * curr * a) / __gcd((i * a), curr);
    if (l == nxt)
      ans += w[i * a];
  }
  return ans;
}
double solve(int i)
{
  if (vis[i])
    return dp[i];
  double p = (double)(sum - sum_divs[i]) / sum; // probabilidade de avancar
  double ret = (double)1 / p;                   // valor esperado de tries ate avancar
  int sum_nxt = 0;
  for (int j = (i + i); j <= n; j += i) // ir para um multiplo de i, mas o jogo nao acaba
  {
    int at = cnt(i, j);
    sum_nxt += at;
    double prob = (double)at / (sum - sum_divs[i]);
    ret += (solve(j) * prob);
  }
  vis[i] = 1;
  return dp[i] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 1; i <= n; i++)
  {
    cin >> w[i];
    sum += w[i];
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = i; j <= n; j += i)
    {
      sum_divs[j] += w[i];
      sum_mul[i] += w[j];
      divs[j].pb(i);
    }
  }
  double ans = solve(1);
  ans -= 1;
  cout << fixed << setprecision(15) << ans << endl;
}
