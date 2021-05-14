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
#define pii pair<int, pi>
#define fir first
#define sec second
#define eps 0.000000001
#define MAXN 100005
#define mod 1000000007

struct event
{
  int time, value, type;
};

bool cmp(event a, event b)
{
  if (a.time != b.time)
    return a.time < b.time;
  return a.type > b.type;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<event> v;
  for (int i = 0; i < n; i++)
  {
    int l, r, h;
    cin >> l >> r >> h;
    v.pb({l, h, 0});
    v.pb({r, h, 1});
  }
  sort(v.begin(), v.end(), cmp);
  int ans = 0, l = -1;
  multiset<int> vals;
  for (int i = 0; i < v.size(); i++)
  {
    if (l == -1)
    {
      l = v[i].time;
      vals.insert(v[i].value);
    }
    else if (v[i].type == 1)
    {
      int curr = *vals.rbegin();
      vals.erase(vals.find(v[i].value));
      if (!vals.size() || *vals.rbegin() != curr)
      {
        int new_t = (!vals.size()) ? -1 : v[i].time;
        int lo = l, hi = v[i].time - 1;
        ans += ((hi - lo + 1) * curr);
        l = new_t;
      }
    }
    else
    {
      int curr = *vals.rbegin();
      vals.insert(v[i].value);
      if (*vals.rbegin() != curr)
      {
        int lo = l, hi = v[i].time - 1;
        ans += ((hi - lo + 1) * curr);
        l = hi + 1;
      }
    }
  }
  cout << ans << endl;
  return 0;
}