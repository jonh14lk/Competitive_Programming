#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define mp make_pair
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 300001
#define MAXL 20
#define mod 1000000009

vector<int> seg(4 * MAXN);
vector<int> lazy(4 * MAXN);
vector<int> v(MAXN);

void add(int i, int l, int r, int diff)
{
  seg[i] += (r - l + 1) * diff;
  if (l != r)
  {
    lazy[l << 1] += diff;
    lazy[(l << 1) | 1] += diff;
  }
}
void update(int i, int l, int r, int ql, int qr, int diff)
{
  if (lazy[i] != 0)
    add(i, l, r, lazy[i]), lazy[i] = 0;
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    add(i, l, r, diff);
    return;
  }
  int mid = (l + r) >> 1;
  update(i << 1, l, mid, ql, qr, diff);
  update((i << 1) | 1, mid + 1, r, ql, qr, diff);
  seg[i] = seg[i << 1] + seg[(i << 1) | 1] ;
}
int query(int l, int r, int ql, int qr, int i)
{
  int mid = (l + r) >> 1;
  if (lazy[i] != 0)
    add(i, l, r, lazy[i]), lazy[i] = 0;
  if (l > r || l > qr || r < ql)
    return 0;
  if (l >= ql && r <= qr)
    return seg[i];
  return query(l, mid, ql, qr, i << 1) + query(mid + 1, r, ql, qr, (i << 1) | 1) ;
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i] = v[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  seg[i] = seg[i << 1] + seg[(i << 1) | 1] ;
}
signed main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  build(0, n - 1, 1);
  int q;
  cin >> q;
  while (q--)
  {
    int l, r;
    char t;
    cin >> t >> l >> r;
    if (t == 'Q')
      cout << query(0, n - 1, l, r, 1) << endl;
    else
      update(1, 0, n - 1, l, l, r - v[l]), v[l] += (r - v[l]);
  }
}
