//https://atcoder.jp/contests/dp/tasks/dp_j
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<pi, int>
#define pci pair<char, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 301
#define mod 1000000007

int n;
vector<int> v;
vector<int> cnt(3);
double dp[MAXN][MAXN][MAXN];

double solve(int i, int j, int k)
{
  if (!i && !j && !k)
    return dp[i][j][k] = 0;
  if (dp[i][j][k] != -1)
    return dp[i][j][k];
  /*
  It is well-known from statistics that for the geometric distribution 
  (counting number of trials before a success, where each independent trial is probability p) 
  the expected value is i / p
  */
  double p = ((double)(i + j + k) / n);
  double ret = 1 / p; // expected number of trials before a success
  if (i)
  {
    double prob = (double)i / (i + j + k); // probabilidade de ser um prato com um sushi
    ret += (solve(i - 1, j, k) * prob);
  }
  if (j)
  {
    double prob = (double)j / (i + j + k); // probabilidade de ser um prato com dois sushis
    ret += (solve(i + 1, j - 1, k) * prob);
  }
  if (k)
  {
    double prob = (double)k / (i + j + k); // probabilidade de ser um prato com tres sushis
    ret += (solve(i, j + 1, k - 1) * prob);
  }
  return dp[i][j][k] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i], cnt[v[i] - 1]++;
  for (int i = 0; i < MAXN; i++)
    for (int j = 0; j < MAXN; j++)
      for (int k = 0; k < MAXN; k++)
        dp[i][j][k] = -1;
  cout << setprecision(15) << solve(cnt[0], cnt[1], cnt[2]) << endl;
  return 0;
}
