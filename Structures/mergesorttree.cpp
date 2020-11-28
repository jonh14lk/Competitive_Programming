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
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007

vector<int> seg[4 * MAXN];
int v[MAXN];

void update(int i, int l, int r, int q, int x)
{
  if (l == r)
  {
    seg[i].clear();
    seg[i].pb(x);
    return;
  }
  int mid = (l + r) >> 1;
  if (q <= mid)
    update(i << 1, l, mid, q, x);
  else
    update((i << 1) | 1, mid + 1, r, q, x);
  // a merge do c++ une os dois vectors, deixando ele ordenado em O(n)
  seg[i].clear();
  merge(seg[i << 1].begin(), seg[i << 1].end(), seg[(i << 1) | 1].begin(), seg[(i << 1) | 1].end(), back_inserter(seg[i]));
}
int query(int l, int r, int ql, int qr, int i, int x)
{
  int mid = (l + r) >> 1;
  if (l > r || l > qr || r < ql)
    return 0;
  if (l >= ql && r <= qr) // quantidade de elementos maiores do que x no range atual
    return seg[i].end() - upper_bound(seg[i].begin(), seg[i].end(), x);
  return query(l, mid, ql, qr, i << 1, x) + query(mid + 1, r, ql, qr, (i << 1) | 1, x);
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i].pb(v[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  // a merge do c++ une os dois vectors, deixando ele ordenado em O(n)
  merge(seg[i << 1].begin(), seg[i << 1].end(), seg[(i << 1) | 1].begin(), seg[(i << 1) | 1].end(), back_inserter(seg[i]));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// merge sort tree
// a segment tree with ordered vectors in range nodes

// example:
// number of elements > x in a range [l, r]

// memory: O(n * log n)
// query: O(log^2 n)
