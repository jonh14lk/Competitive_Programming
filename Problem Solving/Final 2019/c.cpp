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
#define INF 1e16
int n, l, u;
int v[MAXN];
int pref[MAXN];

namespace seg
{
  struct item
  {
    int mx, mn;
  };

  item seg[4 * MAXN];

  int query(int l, int r, int ql, int qr, int i, int x)
  {
    if (l == r)
      return (seg[i].mx >= x && l >= ql && r <= qr) ? l : INF;
    int mid = (l + r) >> 1, at = INF;
    if (seg[i << 1].mx >= x && mid >= ql)
      at = query(l, mid, ql, qr, i << 1, x);
    if (at == INF)
      at = query(mid + 1, r, ql, qr, (i << 1) | 1, x);
    return at;
  }
  int query2(int l, int r, int ql, int qr, int i, int x)
  {
    if (l == r)
      return (seg[i].mn <= x && l >= ql && r <= qr) ? l : INF;
    int mid = (l + r) >> 1, at = INF;
    if (seg[i << 1].mn <= x && mid >= ql)
      at = query2(l, mid, ql, qr, i << 1, x);
    if (at == INF)
      at = query2(mid + 1, r, ql, qr, (i << 1) | 1, x);
    return at;
  }
  void build(int i, int l, int r)
  {
    if (l == r)
    {
      seg[i] = {pref[l], pref[l]};
      return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid);
    build((i << 1) | 1, mid + 1, r);
    seg[i].mx = max(seg[i << 1].mx, seg[(i << 1) | 1].mx);
    seg[i].mn = min(seg[i << 1].mn, seg[(i << 1) | 1].mn);
  }
} // namespace seg
namespace sparse
{
  pi up[2][MAXN][26];

  void build()
  {
    for (int j = 0; j < 2; j++)
    {
      for (int i = 0; i < n; i++)
      {
        if (i == n - 1)
        {
          up[j][i][0] = {i, j};
          continue;
        }
        int idx = INF, type = j, p = pref[i];
        int c = (!j) ? u : l;
        int curr = seg::query(0, n - 1, i + 1, n - 1, 1, (u - c + 1) + p);
        if (curr != -1 && curr < idx)
          idx = curr, type = 0;
        curr = seg::query2(0, n - 1, i + 1, n - 1, 1, (l - c - 1) + p);
        if (curr != -1 && curr < idx)
          idx = curr, type = 1;
        if (idx == INF)
          idx = i;
        up[j][i][0] = {idx, type};
      }
    }
    for (int j = n - 1; j >= 0; j--)
      for (int t = 0; t < 2; t++)
        for (int i = 1; i <= 25; i++)
          up[t][j][i] = up[up[t][j][i - 1].sec][up[t][j][i - 1].fir][i - 1];
  }
  int query(int idx, int type, int r)
  {
    for (int i = 25; i >= 0; i--)
    {
      pi nxt = up[type][idx][i];
      if (nxt.fir <= r)
      {
        idx = nxt.fir;
        type = nxt.sec;
      }
    }
    int p = pref[idx], to_sum = (!type) ? u : l;
    return to_sum + (pref[r] - p);
  }
} // namespace sparse
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> l >> u;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  pref[0] = v[0];
  for (int i = 1; i < n; i++)
    pref[i] = pref[i - 1] + v[i];
  seg::build(1, 0, n - 1);
  sparse::build();
  int q;
  cin >> q;
  while (q--)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    int p = (!a) ? 0 : pref[a - 1];
    int idx = INF, type = 0;
    int curr = seg::query(0, n - 1, a, b, 1, (u - c + 1) + p);
    if (curr != INF && curr < idx)
      idx = curr, type = 0;
    curr = seg::query2(0, n - 1, a, b, 1, (l - c - 1) + p);
    if (curr != INF && curr < idx)
      idx = curr, type = 1;
    if (idx == INF)
    {
      cout << (pref[b] - p) + c << endl;
      continue;
    }
    cout << sparse::query(idx, type, b) << endl;
  }
  return 0;
}