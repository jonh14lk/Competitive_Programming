#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 403
#define mod 1000000007
#define INF 1e7

struct query
{
  int a, b, idx;
};
struct edge
{
  int a, b, c;
};

int n, m, q;
vector<edge> edges;
vector<query> cold[MAXN];
vector<query> hot[MAXN];
int ans[100005];
pi v[MAXN];
int eq[MAXN];
int eq2[MAXN];
int d[MAXN][MAXN];

void solve_hot()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      d[i][j] = (i == j) ? 0 : INF;
  for (auto const &i : edges)
  {
    d[i.a][i.b] = i.c;
    d[i.b][i.a] = i.c;
  }
  for (auto const &i : hot[0])
    ans[i.idx] = d[i.a][i.b];
  for (int i = 1; i <= n; i++)
  {
    int l = v[n - i].sec;
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        d[j][k] = min(d[j][k], d[j][l] + d[l][k]);
    for (auto const &i : hot[i])
      ans[i.idx] = d[i.a][i.b];
  }
}
void solve_cold()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      d[i][j] = (i == j) ? 0 : INF;
  for (auto const &i : edges)
  {
    d[i.a][i.b] = i.c;
    d[i.b][i.a] = i.c;
  }
  for (auto const &i : cold[0])
    ans[i.idx] = d[i.a][i.b];
  for (int i = 1; i <= n; i++)
  {
    int l = v[i - 1].sec;
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        d[j][k] = min(d[j][k], d[j][l] + d[l][k]);
    for (auto const &i : cold[i])
      ans[i.idx] = d[i.a][i.b];
  }
}
void calc()
{
  int ptr = 0;
  for (int i = 1; i <= n; i++)
  {
    int ini = v[ptr].fir;
    while (ptr + 1 < n && v[ptr + 1].fir == ini)
      ptr++;
    eq[i] = ptr + 1;
    ptr = min(ptr + 1, n - 1);
  }
  ptr = n - 1;
  for (int i = 1; i <= n; i++)
  {
    int ini = v[ptr].fir;
    while (ptr - 1 >= 0 && v[ptr - 1].fir == ini)
      ptr--;
    eq2[i] = n - ptr;
    ptr = max(ptr - 1, 0);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir;
    v[i].sec = i;
  }
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    edges.pb({a, b, c});
  }
  sort(v, v + n);
  calc();
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int a, b, c, t;
    cin >> a >> b >> c >> t;
    a--, b--;
    if (!t)
      cold[eq[c]].pb({a, b, i});
    else
      hot[eq2[c]].pb({a, b, i});
  }
  solve_cold();
  solve_hot();
  for (int i = 0; i < q; i++)
    (ans[i] == INF) ? cout << -1 << endl : cout << ans[i] << endl;
}