#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define lli long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 600005
#define mod 1000000007

bool has_zero[MAXN];
bool has_one[MAXN];
bool has_int[MAXN];
int parent[MAXN * 21];
int sz[MAXN * 21];
vector<pii> edges;

lli modpow(int x, int y)
{
  int z = 1;
  while (y)
  {
    if (y & 1)
      z = (z * 1ll * x) % mod;
    x = (x * 1ll * x) % mod;
    y >>= 1;
  }
  return z;
}
int find_set(int i)
{
  return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
}
void make_set(int x, int y)
{
  x = find_set(x);
  y = find_set(y);
  if (x != y)
  {
    if (sz[x] > sz[y])
      swap(x, y);
    parent[x] = y;
    sz[y] += sz[x];
  }
}
void init()
{
  for (int i = 0; i < MAXN * 21; i++)
  {
    parent[i] = i;
    sz[i] = 1;
  }
}
void add_edge(int l, int r, int a, int b)
{
  int len = r - l + 1;
  for (int i = 20; i >= 0; i--)
  {
    if (len & (1 << i))
    {
      edges.pb({i, {l, a}});
      l += (1 << i);
      a += (1 << i);
    }
  }
}
void imp()
{
  cout << 0 << endl;
  exit(0);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  string t = s;
  reverse(t.begin(), t.end());
  s = s + t;
  for (int i = 0; i < q; i++)
  {
    int l, r;
    cin >> l >> r;
    l--, r--;
    if (l == r)
      continue;
    int a = n + ((n - 1) - r), b = n + ((n - 1) - l);
    add_edge(l, r, a, b);
  }
  sort(edges.begin(), edges.end());
  deque<pii> pq;
  for (auto const &i : edges)
  {
    pq.push_front(i);
  }
  init();
  while (!pq.empty())
  {
    pii v = pq.front();
    pq.pop_front();
    int a = (v.fir * MAXN) + v.sec.fir;
    int b = (v.fir * MAXN) + v.sec.sec;
    if (find_set(a) == find_set(b))
      continue;
    make_set(a, b);
    if (v.fir > 0)
    {
      int sz = v.fir - 1;
      pq.push_front({sz, {v.sec.fir, v.sec.sec}});
      pq.push_front({sz, {v.sec.fir + (1 << sz), v.sec.sec + (1 << sz)}});
    }
  }
  for (int i = 0, j = s.size() - 1; i < n; i++, j--)
  {
    make_set(i, j);
  }
  for (int i = 0; i < n; i++)
  {
    int p = find_set(i);
    if (s[i] == '1')
      has_one[p] = 1;
    else if (s[i] == '0')
      has_zero[p] = 1;
    else
      has_int[p] = 1;
  }
  int ans = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (has_zero[i] && has_one[i])
      imp();
    if (has_int[i] && !has_zero[i] && !has_one[i])
      ans++;
  }
  cout << modpow(2, ans) << endl;
  return 0;
}
