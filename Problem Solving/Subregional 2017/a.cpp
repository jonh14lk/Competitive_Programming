#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

vector<vector<int>> seg(4 * MAXN, vector<int>(9, 0));
vector<int> lazy(4 * MAXN);
vector<int> ans(9);

void add(int i, int l, int r, int diff)
{
  vector<int> vv(9);
  for (int j = 0; j < 9; j++)
  {
    int at = (j + diff) % 9;
    vv[at] = seg[i][j];
  }
  for (int j = 0; j < 9; j++)
    seg[i][j] = vv[j];
  if (l != r)
  {
    lazy[i << 1] += diff;
    lazy[(i << 1) | 1] += diff;
  }
  lazy[i] = 0;
}
void update(int i, int l, int r, int ql, int qr, int diff)
{
  if (lazy[i])
    add(i, l, r, lazy[i]);
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
  for (int j = 0; j < 9; j++)
    seg[i][j] = seg[i << 1][j] + seg[(i << 1) | 1][j];
}
void query(int l, int r, int ql, int qr, int i)
{
  if (lazy[i])
    add(i, l, r, lazy[i]);
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    for (int j = 0; j < 9; j++)
      ans[j] = ans[j] + seg[i][j];
    return;
  }
  int mid = (l + r) >> 1;
  query(l, mid, ql, qr, i << 1);
  query(mid + 1, r, ql, qr, (i << 1) | 1);
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i][1] = 1;
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  for (int j = 0; j < 9; j++)
    seg[i][j] = seg[i << 1][j] + seg[(i << 1) | 1][j];
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  build(0, n - 1, 1);
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    for (int i = 0; i < 9; i++)
      ans[i] = 0;
    query(0, n - 1, l, r, 1);
    int best = 0, at = 0;
    for (int i = 0; i < 9; i++)
    {
      if (ans[i] >= best)
      {
        best = ans[i];
        at = i;
      }
    }
    update(1, 0, n - 1, l, r, at);
  }
  for (int i = 0; i < n; i++)
  {
    for (int i = 0; i < 9; i++)
      ans[i] = 0;
    query(0, n - 1, i, i, 1);
    for (int i = 0; i < 9; i++)
    {
      if (ans[i])
      {
        cout << i << endl;
        break;
      }
    }
  }
}