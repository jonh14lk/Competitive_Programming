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
#define MAXN 100005
#define mod 998244353

int n, k;
double dp[101][1 << 9];
vector<pi> v;
vector<pi> cap;

double d(pi a, pi b)
{
  return sqrt(((a.fir - b.fir) * (a.fir - b.fir)) + ((a.sec - b.sec) * (a.sec - b.sec)));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < k; i++)
  {
    int a, b;
    cin >> a >> b;
    cap.pb({a, b});
  }
  for (int i = k; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    v.pb({a, b});
  }
  for (int i = 0; i <= 100; i++)
    for (int j = 0; j < (1 << 9); j++)
      dp[i][j] = 1e9;
  for (int i = 0; i < k; i++)
    for (int j = 0; j < v.size(); j++)
      dp[j][1 << i] = d(cap[i], v[j]);
  for (int mask = 2; mask < (1 << k); mask++)
  {
    for (int i = 0; i < v.size(); i++)
    {
      for (int mask2 = 1; mask2 < mask; mask2++)
      {
        if (!((mask & mask2) == mask2))
          continue;
        int mask3 = mask ^ mask2;
        dp[i][mask] = min(dp[i][mask], dp[i][mask2] + dp[i][mask3]);
      }
      for (int j = 0; j < v.size(); j++)
        dp[j][mask] = min(dp[j][mask], dp[i][mask] + d(v[i], v[j]));
    }
  }
  double ans = 1e9;
  for (int i = 0; i <= 100; i++)
    ans = min(ans, dp[i][(1 << k) - 1]);
  cout << fixed << setprecision(5) << ans << endl;
  return 0;
}
// toda capital tem que ter grau 1
// nao capitais podem ter mais de uma aresta
// qual o custo minimo para ligar as k capitais
// dp[i][mask]
// i -> um vertice das nao capitais que vou adicionar umas capitais a ele
// mask -> capitais que ja tao conectadas
// ir montando novas masks baseadas nas masks menores que eu ja calculei
// a resposta eh o menor custo que eu preciso chegar em algum estado
// no qual a mask seja (1 << k) - 1