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

void update(int i, int l, int r, int ql, int qr, int diff)
{
  if (lazy[i] != 0)
  {
    seg[i] += (r - l + 1) * lazy[i];
    if (l != r)
    {
      lazy[i * 2 + 1] += lazy[i];
      lazy[i * 2 + 2] += lazy[i];
    }
    lazy[i] = 0;
  }
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    seg[i] += (r - l + 1) * diff;
    if (l != r)
    {
      lazy[i * 2 + 1] += diff;
      lazy[i * 2 + 2] += diff;
    }
    return;
  }
  int mid = (l + r) / 2;
  update(i * 2 + 1, l, mid, ql, qr, diff);
  update(i * 2 + 2, mid + 1, r, ql, qr, diff);
  seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
}
int query(int l, int r, int ql, int qr, int i)
{
  if (lazy[i] != 0)
  {
    seg[i] += (r - l + 1) * lazy[i];
    if (l != r)
    {
      lazy[i * 2 + 1] += lazy[i];
      lazy[i * 2 + 2] += lazy[i];
    }
    lazy[i] = 0;
  }
  if (l > r || l > qr || r < ql)
    return 0;
  if (l >= ql && r <= qr)
    return seg[i];
  int mid = (l + r) / 2;
  return query(l, mid, ql, qr, 2 * i + 1) + query(mid + 1, r, ql, qr, 2 * i + 2);
}
void build(int l, int r, int i)
{
  if (l > r)
    return;
  if (l == r)
  {
    seg[i] = v[l];
    return;
  }
  int mid = (l + r) / 2;
  build(l, mid, 2 * i + 1);
  build(mid + 1, r, 2 * i + 2);
  seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
}
signed main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  build(0, n - 1, 0);
  int q;
  cin >> q;
  while (q--)
  {
    int l, r;
    char t;
    cin >> t >> l >> r;
    if (t == 'Q')
      cout << query(0, n - 1, l, r, 0) << endl;
    else
      update(0, 0, n - 1, l, l, r - v[l]), v[l] += (r - v[l]);
  }
}
