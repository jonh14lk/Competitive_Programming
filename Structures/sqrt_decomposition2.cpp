#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

int n, q;
vector<int> v;

namespace mo
{
  struct query
  {
    int idx, l, r, t;
  };
  struct update
  {
    int i, x;
  };

  int block;
  vector<query> queries;
  vector<update> updates;
  vector<int> ans;

  bool cmp(query x, query y)
  {
    if (x.l / block != y.l / block)
      return x.l / block < y.l / block;
    if (x.r / block != y.r / block)
      return x.r / block < y.r / block;
    return x.t < y.t;
  }
  void sqrt_decomposition()
  {
    block = 2800; // (2 * n) ^ 0.666
    sort(queries.begin(), queries.end(), cmp);
    ans.resize(queries.size());
    int curr_left = 0, curr_right = 0, curr_sum = 0, curr_t = 0;
    for (int i = 0; i < queries.size(); i++)
    {
      int idx = queries[i].idx;
      int l = queries[i].l;
      int r = queries[i].r;
      int t = queries[i].t;
      while (curr_right <= r)
      {
        curr_sum += v[curr_right];
        curr_right++;
      }
      while (curr_left > l)
      {
        curr_left--;
        curr_sum += v[curr_left];
      }
      while (curr_right > r + 1)
      {
        curr_right--;
        curr_sum -= v[curr_right];
      }
      while (curr_left < l)
      {
        curr_sum -= v[curr_left];
        curr_left++;
      }
      while (curr_t > t)
      {
        curr_t--;
        if (l <= updates[curr_t].i && r >= updates[curr_t].i)
          curr_sum -= updates[curr_t].x;
        v[updates[curr_t].i] -= updates[curr_t].x;
      }
      while (curr_t < t)
      {
        if (l <= updates[curr_t].i && r >= updates[curr_t].i)
          curr_sum += updates[curr_t].x;
        v[updates[curr_t].i] += updates[curr_t].x;
        curr_t++;
      }
      ans[idx] = curr_sum;
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < q; i++)
  {
    int type;
    cin >> type;
    if (!type)
    {
      mo::update curr;
      cin >> curr.i >> curr.x;
      mo::updates.pb(curr);
    }
    else
    {
      mo::query curr;
      cin >> curr.l >> curr.r;
      curr.r--;
      curr.idx = mo::queries.size();
      curr.t = mo::updates.size();
      mo::queries.pb(curr);
    }
  }
  mo::sqrt_decomposition();
  for (auto const &i : mo::ans)
    cout << i << endl;
}
//https://judge.yosupo.jp/problem/point_add_range_sum
