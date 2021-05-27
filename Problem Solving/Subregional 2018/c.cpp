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

vector<pi> a[2];

namespace ms_tree
{
  vector<int> seg[4 * MAXN];
  int v[MAXN];

  int query(int l, int r, int ql, int qr, int i, int x)
  {
    int mid = (l + r) >> 1;
    if (l > r || l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr) // quantidade de elementos maiores do que x no range atual
      return seg[i].end() - upper_bound(seg[i].begin(), seg[i].end(), x);
    return query(l, mid, ql, qr, i << 1, x) + query(mid + 1, r, ql, qr, (i << 1) | 1, x);
  }
  void build(int l, int r, int i, int idx)
  {
    if (l == r)
    {
      seg[i].pb(a[idx][l].sec);
      return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1, idx);
    build(mid + 1, r, (i << 1) | 1, idx);
    merge(seg[i << 1].begin(), seg[i << 1].end(), seg[(i << 1) | 1].begin(), seg[(i << 1) | 1].end(), back_inserter(seg[i]));
  }
}; // namespace ms_tree
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, h, v;
  cin >> n >> m >> h >> v;
  a[0].resize(h);
  a[1].resize(v);
  for (int i = 0; i < h; i++)
    cin >> a[0][i].fir >> a[0][i].sec;
  for (int i = 0; i < v; i++)
    cin >> a[1][i].fir >> a[1][i].sec;
  sort(a[0].begin(), a[0].end());
  sort(a[1].begin(), a[1].end());
  int ans = (h + v) + (h * v);
  for (int j = 0; j <= 1; j++)
  {
    ms_tree::build(0, a[j].size() - 1, 1, j);
    for (int i = 0; i < a[j].size(); i++)
      ans += ms_tree::query(0, a[j].size() - 1, 0, i, 1, a[j][i].sec);
    for (int i = 0; i < 4 * MAXN; i++)
      ms_tree::seg[i].clear();
  }
  cout << ans + 1 << endl;
  return 0;
}
// cada corte separa uma area em 2
// cada intersecção separa uma area em 2 also
// a resposta inicial eh (h + v) + (h * v)
// pois cada corte na horizontal se intersecta com cada um na vertical
// e cada corte em si separa a pizza em 2 partes que antes nao existiam
// dois cortes i e j se intersectam caso:
// l[i] < l[j] && r[i] > r[j]
// com isso, podemos contar as intersecçoes achando esses pares validos
// e ir adicionando a resposta