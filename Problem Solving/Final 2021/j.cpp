#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000001
#define mod 998244353

int w, h;
vector<pi> v[4];

int add(int x, int y, int id)
{
  if (y == 0)
  {
    v[0].pb({x, id});
    return 1;
  }
  else if (x == w)
  {
    v[1].pb({y, id});
    return 1;
  }
  else if (y == h)
  {
    v[2].pb({-x, id});
    return 1;
  }
  else if (x == 0)
  {
    v[3].pb({-y, id});
    return 1;
  }
  return 0;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> w >> h;
  int n;
  cin >> n;
  vector<int> freq(n, 0);
  for (int i = 0; i < n; i++)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    freq[i] += add(a, b, i);
    freq[i] += add(c, d, i);
  }
  vector<pi> a;
  for (int i = 0; i < 4; i++)
  {
    sort(v[i].begin(), v[i].end());
    for (auto const &j : v[i])
      a.pb(j);
  }
  stack<int> st;
  vector<int> cnt(n, 0);
  for (auto const &i : a)
  {
    int x = i.sec;
    if (freq[x] != 2)
      continue;
    cnt[x]++;
    if (cnt[x] == 2)
    {
      if (!st.size() || st.top() != x)
      {
        cout << "N\n";
        return 0;
      }
      st.pop();
    }
    else
    {
      st.push(x);
    }
  }
  cout << "Y\n";
  return 0;
}