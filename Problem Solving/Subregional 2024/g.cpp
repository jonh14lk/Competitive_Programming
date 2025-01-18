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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct segtree
{
  int n;
  vector<int> v;
  vector<int> seg;
  vector<int> lazy;

  segtree() {}
  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
  }
  int single(int x)
  {
    return x;
  }
  int neutral()
  {
    return -1e18;
  }
  int merge(int a, int b)
  {
    return max(a, b);
  }
  void add(int i, int l, int r, int diff)
  {
    seg[i] += diff;
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
    seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (lazy[i])
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return neutral();
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
  int qry(int l, int r)
  {
    int lo = l, hi = r;
    while (lo < hi)
    {
      int mid = (lo + hi) >> 1;
      (query(0, n - 1, l, mid, 1) > 0) ? hi = mid : lo = mid + 1;
    }
    assert(lo <= r);
    return lo;
  }
  void upd(int l, int r, int x)
  {
    if (l > r)
      return;
    update(1, 0, n - 1, l, r, x);
  }
};

segtree st;
int n, root;
int sz[MAXN];
int win[MAXN];
int qt[MAXN];
int coef[MAXN];
int delta[MAXN];
int par[MAXN];
pi child[MAXN];

namespace hld
{
  int cur_pos;
  int pos[MAXN];
  int head[MAXN];
  int l_head[MAXN];
  int r_head[MAXN];
  int rev_pos[MAXN];

  void init()
  {
    cur_pos = 0;
  }
  void decompose(int s, int h)
  {
    if (s == h)
    {
      l_head[h] = cur_pos;
    }
    if (s < n) // folha
    {
      head[s] = h;
      r_head[h] = cur_pos;
      pos[s] = cur_pos++;
      rev_pos[cur_pos - 1] = s;
      st.upd(pos[s], pos[s], delta[s]);
      return;
    }
    head[child[s].sec] = h;
    pos[child[s].sec] = cur_pos++;
    rev_pos[cur_pos - 1] = child[s].sec;
    st.upd(pos[child[s].sec], pos[child[s].sec], delta[s]);
    decompose(child[s].fir, h);
    if (child[s].sec >= n) // filho da esquerda nao folha, decompoe num novo path
    {
      decompose(child[s].sec, child[s].sec);
    }
  }
  void upd(int s, int x)
  {
    while (s != root)
    {
      st.upd(pos[s], pos[s], x);
      st.upd(l_head[head[s]], pos[s] - 1, -x);
      win[head[s]] = win[rev_pos[st.qry(l_head[head[s]], r_head[head[s]])]];
      s = head[s];
    }
  }
}
void dfs(int s)
{
  sz[s] = 1;
  if (s < n)
  {
    win[s] = s;
    coef[s] = qt[s];
    delta[s] = coef[s];
    return;
  }
  dfs(child[s].fir);
  dfs(child[s].sec);
  sz[s] += sz[child[s].fir];
  sz[s] += sz[child[s].sec];
  if (sz[child[s].fir] < sz[child[s].sec])
    swap(child[s].fir, child[s].sec);
  coef[s] = coef[child[s].fir] + coef[child[s].sec];
  if (child[s].fir < child[s].sec)
    delta[s] = coef[child[s].sec] - (coef[child[s].fir] + 1);
  else
    delta[s] = (coef[child[s].sec] + 1) - coef[child[s].fir];
  win[s] = (delta[s] > 0) ? win[child[s].sec] : win[child[s].fir];
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> qt[i];
    qt[i] *= 2;
  }
  for (int i = n; i < n + n - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    par[a] = i;
    par[b] = i;
    child[i] = {a, b};
  }
  root = n + n - 2;
  int sz = root + 1;
  dfs(root);
  cout << win[root] + 1 << endl;
  st = segtree(2 * n);
  hld::init();
  hld::decompose(root, root);
  int q;
  cin >> q;
  while (q--)
  {
    int n, x;
    cin >> n >> x;
    n--;
    hld::upd(n, 2 * x);
    cout << win[root] + 1 << endl;
  }
}