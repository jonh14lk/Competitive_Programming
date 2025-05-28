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
#define MAXN 200005

vector<int> seg;

int single(int x)
{
  return x;
}
int neutral()
{
  return 1e18;
}
int merge(int a, int b)
{
  return min(a, b);
}
int query(int l, int r, int ql, int qr, int i)
{
  int mid = (l + r) >> 1;
  if (l > r || l > qr || r < ql)
    return neutral();
  if (l >= ql && r <= qr)
    return seg[i];
  return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
}
void build(int l, int r, int i, vector<int> &v)
{
  if (l == r)
  {
    seg[i] = single(v[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1, v);
  build(mid + 1, r, (i << 1) | 1, v);
  seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  int m = n + n;
  vector<int> v(m);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = n; i < m; i++)
    v[i] = v[i - n];
  vector<int> v2(m);
  for (int i = 0; i < m; i++)
    v2[i] = v[i] - (i * k);
  seg.resize(4 * m);
  build(0, m - 1, 1, v2);
  for (int i = 0; i < n; i++)
  {
    int l = i, r = n + n - 1;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      int curr = query(0, m - 1, i, mid, 1);
      (curr < v2[i]) ? r = mid : l = mid + 1;
    }
    int ans = (l % n) + 1;
    cout << ans << " \n"[i == (n - 1)];
  }
  return 0;
}
// se eu tou saindo do indice i pro indice j
// quero saber se
// v[j] >= (j - i) * k + v[i]
// v[j] >= jk - ik + v[i]
// v[j] - jk >= -ik + v[i] -> podemos olhar para essa condicao