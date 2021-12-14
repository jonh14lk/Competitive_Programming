#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct implcit_seg
{
  int l, r;
  int sum, lazy;
  implcit_seg *left_child = nullptr;
  implcit_seg *right_child = nullptr;

  implcit_seg(int l, int r) : l(l), r(r)
  {
    sum = 0;
    lazy = 0;
  }
  void check_childs()
  {
    if (!left_child && l != r)
    {
      int mid = (l + r) >> 1;
      left_child = new implcit_seg(l, mid);
      right_child = new implcit_seg(mid + 1, r);
    }
  }
  void add(int x)
  {
    sum += (r - l + 1) * x;
    if (l != r)
    {
      check_childs();
      left_child->lazy += x;
      right_child->lazy += x;
    }
    lazy = 0;
  }
  void upd(int ql, int qr, int x)
  {
    add(lazy);
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(x);
      return;
    }
    check_childs();
    left_child->upd(ql, qr, x);
    right_child->upd(ql, qr, x);
    sum = left_child->sum + right_child->sum;
  }
  void upd(int k, int x)
  {
    sum += x;
    check_childs();
    if (left_child)
    {
      if (k <= left_child->r)
        left_child->upd(k, x);
      else
        right_child->upd(k, x);
    }
  }
  int qry(int ql, int qr)
  {
    add(lazy);
    if (l > r || l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return sum;
    check_childs();
    return left_child->qry(ql, qr) + right_child->qry(ql, qr);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  implcit_seg *s = new implcit_seg(0, n - 1);
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int l, r, x;
      cin >> l >> r >> x;
      if (l == r - 1) // point update
        s->upd(l, x);
      else // range update
        s->upd(l, r - 1, x);
    }
    else
    {
      int l, r;
      cin >> l >> r;
      cout << s->qry(l, r - 1) << endl; // range sum
    }
  }
  return 0;
}