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
#define mod 1000000007

int f[MAXN];     // f[i] -> quantos "itens" com valor i tem
bitset<MAXN> dp; // dp[i] = 1, se existe um subset com soma i
// garantir que a soma de todo mundo seja < MAXN
void subset_sum(vector<int> &v)
{
  for (auto const &i : v)
  {
    f[i]++;
  }
  dp[0] = 1;
  for (int i = 1; i < MAXN; i++)
  {
    while (f[i] > 2)
    {
      f[i * 2]++;
      f[i] -= 2;
    }
    while (f[i]--)
      dp |= (dp << i);
  }
}

// https://github.com/gabrielpessoa1/ICPC-Library/blob/master/code/Miscellaneous/SubsetSum.cpp
/*
 Given N non-negative integer weights w and a non-negative target t,
 computes the maximum S <= t such that S is the sum of some subset of the weights.
 O(N * max(w[i]))
*/
int knapsack(vector<int> w, int t)
{
  int a = 0, b = 0;
  while (b < w.size() && a + w[b] <= t)
  {
    a += w[b++];
  }
  if (b == w.size())
  {
    return a;
  }
  int m = *max_element(w.begin(), w.end());
  vector<int> u, v(2 * m, -1);
  v[a + m - t] = b;
  for (int i = b; i < w.size(); i++)
  {
    u = v;
    for (int x = 0; x < m; x++)
    {
      v[x + w[i]] = max(v[x + w[i]], u[x]);
    }
    for (int x = 2 * m; --x > m;)
    {
      for (int j = max(0ll, u[x]); j < v[x]; j++)
        v[x - w[j]] = max(v[x - w[j]], j);
    }
  }
  a = t;
  while (v[a + m - t] < 0)
  {
    a--;
  }
  return a;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}