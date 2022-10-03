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
#define MAXN 500001
#define mod 1000000007

struct item
{
  int nxt, sum;
};

int n, q;
int v[MAXN];
item st[MAXN][21];

signed main()
{
  cin >> n >> q;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < n; i++)
  {
    st[i][0].nxt = min(i + 1, n - 1);
    st[i][0].sum = v[st[i][0].nxt];
  }
  for (int i = 1; i < 21; i++)
  {
    for (int v = 0; v < n; v++)
    {
      st[v][i].nxt = st[st[v][i - 1].nxt][i - 1].nxt;
      st[v][i].sum = st[v][i - 1].sum + st[st[v][i - 1].nxt][i - 1].sum;
    }
  }
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    r--;
    int ans = v[l], len = r - l;
    for (int i = 20; i >= 0; i--)
    {
      if (len & (1 << i))
      {
        ans += st[l][i].sum;
        l = st[l][i].nxt;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
// simple range sum query with binary lifting
// https://judge.yosupo.jp/problem/static_range_sum