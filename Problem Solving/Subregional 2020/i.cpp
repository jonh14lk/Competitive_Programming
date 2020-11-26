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
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007

vector<int> seg[MAXN];
vector<int> lazy[MAXN];
vector<int> adj[MAXN];
int dp[MAXN][2];

int modpow(int x, int y)
{
  int z = 1;
  while (y)
  {
    if (y & 1)
      z = (z * x) % mod;
    x = (x * x) % mod;
    y >>= 1;
  }
  return z;
}
int inverse(int x)
{
  return modpow(x, mod - 2);
}
int divide(int x, int y)
{
  return (x * inverse(y)) % mod;
}
int subtract(int x, int y)
{
  return ((x + mod) - y) % mod;
}
int multiplicate(int x, int y)
{
  return (x * y) % mod;
}
int sum(int x, int y)
{
  return (x + y) % mod;
}
int single(int x)
{
  return x;
}
int neutral()
{
  return 1;
}
int merge(int a, int b)
{
  return multiplicate(a, b);
}
void add(int v, int i, int l, int r, int diff)
{
  seg[v][i] = multiplicate(seg[v][i], modpow(diff, (r - l + 1)));
  if (l != r)
  {
    lazy[v][i << 1] = multiplicate(lazy[v][i << 1], diff);
    lazy[v][(i << 1) | 1] = multiplicate(lazy[v][(i << 1) | 1], diff);
  }
  lazy[v][i] = 1;
}
void update(int v, int i, int l, int r, int ql, int qr, int diff)
{
  if (ql > qr || ql > r)
    return;
  if (lazy[v][i] != 1)
    add(v, i, l, r, lazy[v][i]);
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    add(v, i, l, r, diff);
    return;
  }
  int mid = (l + r) >> 1;
  update(v, i << 1, l, mid, ql, qr, diff);
  update(v, (i << 1) | 1, mid + 1, r, ql, qr, diff);
  seg[v][i] = merge(seg[v][i << 1], seg[v][(i << 1) | 1]);
}
int query(int v, int l, int r, int ql, int qr, int i)
{
  if (lazy[v][i] != 1)
    add(v, i, l, r, lazy[v][i]);
  if (l > r || l > qr || r < ql)
    return neutral();
  if (l >= ql && r <= qr)
    return seg[v][i];
  int mid = (l + r) >> 1;
  return merge(query(v, l, mid, ql, qr, i << 1), query(v, mid + 1, r, ql, qr, (i << 1) | 1));
}
void dfs(int s, int p)
{
  if (adj[s].size() == 1 && p != -1)
  {
    dp[s][0] = 1;
    dp[s][1] = 1;
    return;
  }
  int prod = 1, idx = 0, sz = (p == -1) ? adj[s].size() : adj[s].size() - 1;
  seg[s].assign(4 * sz, 1);
  lazy[s].assign(4 * sz, 1);
  for (auto const &v : adj[s])
  {
    if (v == p)
      continue;
    dfs(v, s);
    update(s, 1, 0, sz - 1, 0, idx - 1, dp[v][0]);
    update(s, 1, 0, sz - 1, idx + 1, sz - 1, dp[v][0]);
    prod = multiplicate(prod, dp[v][0]);
    idx++;
  }
  dp[s][1] = 0, idx = 0;
  for (auto const &v : adj[s])
  {
    if (v == p)
      continue;
    int curr = multiplicate(query(s, 0, sz - 1, idx, idx, 1), dp[v][1]);
    dp[s][1] = sum(dp[s][1], curr);
    idx++;
  }
  dp[s][0] = sum(prod, dp[s][1]);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int k;
    cin >> k;
    k--;
    adj[i].pb(k);
    adj[k].pb(i);
  }
  dfs(0, -1);
  cout << dp[0][0] << endl;
  return 0;
}
// para saber o valor de todos os nos de uma subarvore:
// 1- pergunto pelo valor de todas as folhas
// 2- pergunto pelo valor de todas as folhas exceto uma
// e pergunto por um outro no que seja um ancestral
// dessa folha que eu nao perguntei

// dp[i][j]
// 2 >= i <= 10^5
// 0 >= j <= 1
// dp[i][0] -> quantidade de jeitos de ja ter todos os valores na subarvore de i
// dp[i][1] -> falta mais uma query para saber todos os valores da subarvore de i

// para uma folha:
// dp[i][0] = 1
// dp[i][1] = 1
// para outros nos(sendo k um filho do no i):
// dp[i][1] = ((produtorio dp[k][0]) / dp[k][0]) * dp[k][1]
// dp[i][0] = (produtorio dp[k][0]) + dp[i][1]
