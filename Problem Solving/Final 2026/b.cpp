#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

struct segtree
{
  int n;
  vector<int> seg;

  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return a + b;
  }
  segtree(int sz)
  {
    n = 1;
    while (n < sz)
      n <<= 1;
    seg.assign(n << 1, neutral());
  }
  void upd(int i, int value)
  {
    seg[i += n] += value;
    for (i >>= 1; i; i >>= 1)
      seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r)
  {
    int ansl = neutral(), ansr = neutral();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
        ansl = merge(ansl, seg[l++]);
      if (r & 1)
        ansr = merge(seg[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};
struct cat
{
  int x, y, w, id;
};
int cross(int x1, int y1, int x2, int y2)
{
  return x1 * y2 - x2 * y1;
}
bool cmp(cat a, cat b)
{
  return cross(a.x, a.y, b.x, b.y) > 0;
}
bool cmp2(cat a, cat b)
{
  return cross(a.x, a.y, b.x, b.y) < 0;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, d;
  cin >> n >> d;
  vector<cat> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x >> v[i].y >> v[i].w;
    v[i].id = i;
  }
  sort(v.begin(), v.end(), cmp);
  vector<int> ord(n);
  for (int i = 0; i < n; i++)
  {
    ord[i] = v[i].id;
    v[i].x -= d;
  }
  sort(v.begin(), v.end(), cmp2);
  vector<int> pos(n);
  for (int i = 0; i < n; i++)
  {
    pos[v[i].id] = i;
  }
  segtree st(n);
  int ans = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    int p = pos[ord[i]];
    ans += v[p].w * st.qry(0, p);
    st.upd(p, v[p].w);
  }
  cout << ans << endl;
}
