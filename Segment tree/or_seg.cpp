#include <bits/stdc++.h> // teste de seg de bitwise or
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 10000001
#define MAXL 101
#define mod 998244353

int v[100000];
int seg[400000];

void update(int i, int l, int r, int pos, int x)
{
  if (l == r)
  {
    seg[i] = x;
  }
  else
  {
    int mid = (l + r) / 2;
    if (pos <= mid)
    {
      update(2 * i, l, mid, pos, x);
    }
    else
    {
      update((2 * i) + 1, mid + 1, r, pos, x);
    }
    seg[i] = seg[2 * i] | seg[(2 * i) + 1];
  }
}
int query(int i, int l, int r, int ql, int qr)
{
  if (l >= ql && r <= qr)
  {
    return seg[i];
  }
  if (l > qr || r < ql)
  {
    return 0;
  }
  int mid = (l + r) / 2;
  return query(2 * i, l, mid, ql, qr) | query((2 * i) + 1, mid + 1, r, ql, qr);
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i] = v[l];
    return;
  }
  int mid = (l + r) / 2;
  build(l, mid, 2 * i);
  build(mid + 1, r, (2 * i) + 1);
  seg[i] = seg[2 * i] | seg[(2 * i) + 1];
}
signed main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    v[i] = pow(2, v[i]);
  }
  build(0, n - 1, 1);
  int q;
  cin >> q;
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    int x = query(1, 0, n - 1, l, r), ans = 0;
    while (x > 0)
    {
      if (x & 1)
        ans++;
      x = x / 2;
    }
    cout << ans << endl;
  }
  return 0;
}
