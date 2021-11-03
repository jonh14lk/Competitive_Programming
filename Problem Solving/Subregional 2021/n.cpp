#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005

int n;
vector<vector<int>> seg;

void build(vector<int> &v)
{
  n = 1;
  while (n < v.size())
    n <<= 1;
  seg.resize(n << 1);
  for (int i = 0; i < v.size(); i++)
    seg[i + n].pb(v[i]);
  for (int i = n - 1; i; i--)
    merge(seg[i << 1].begin(), seg[i << 1].end(), seg[(i << 1) | 1].begin(), seg[(i << 1) | 1].end(), back_inserter(seg[i]));
}
int qry(int l, int r, int x)
{
  int ans = 0;
  for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
  {
    if (l & 1)
      ans += lower_bound(seg[l].begin(), seg[l].end(), x) - seg[l].begin(), l++;
    if (r & 1)
      r--, ans += lower_bound(seg[r].begin(), seg[r].end(), x) - seg[r].begin();
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  build(v);
  while (q--)
  {
    int a, p, f;
    cin >> a >> p >> f;
    a--;
    (v[a] >= p) ? cout << 0 << endl : cout << f - qry(a + 1, a + f, p) << endl;
  }
  return 0;
}