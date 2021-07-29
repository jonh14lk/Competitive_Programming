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
#define MAXN 8001
#define mod 1000000007

int dp[MAXN];
int dp2[MAXN];

signed main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> sor(n);
  for (int i = 0; i < n; i++)
    cin >> v[i], sor[i] = v[i];
  sort(sor.rbegin(), sor.rend());
  int max_cost = -1;
  for (int i = 0; i < n; i++)
  {
    max_cost = max(max_cost, v[i]);
    dp[i] = max_cost;
  }
  cout << dp[n - 1] << " " << max_cost << endl;
  for (int k = 1; k < n; k++)
  {
    stack<pi> t;
    stack<int> ans;
    for (int i = k - 1; i < n; i++)
    {
      int new_dp = 1e18, idx = -1;
      while (!t.empty() && v[i] >= t.top().fir)
      {
        if (dp[t.top().sec] < new_dp)
        {
          new_dp = dp[t.top().sec];
          idx = t.top().sec;
        }
        ans.pop();
        t.pop();
      }
      int curr_ans = (ans.empty()) ? 1e18 : ans.top();
      dp2[i] = min(new_dp + v[i], curr_ans);
      if (i > k - 1)
      {
        ans.push(min(curr_ans, new_dp + v[i]));
        t.push({v[i], idx});
      }
      ans.push(1e18);
      t.push({0, i});
    }
    max_cost += sor[k];
    for (int i = 0; i < n; i++)
      dp[i] = dp2[i];
    cout << dp[n - 1] << " " << max_cost << endl;
  }
  return 0;
}
// para o maior custo:
// vai ser sempre os k maiores, pois como o custo de um
// subarray sempre eh o maior daquele subarray, basta particionar
// de forma com que os k maiores estejam em subarrays diferentes

// para o menor custo:
// podemos escrever dp[k][j] como o menor valor
// para particionar os j + 1 primeiros elementos
// usando k partições
// com isso
// dp[k][j] = min(dp[k - 1][i] + max({v[i + 1], ..., v[j]}))
// para algum i < j
// note que não podemos usar d&c dp otimization aqui
