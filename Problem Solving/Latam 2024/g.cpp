#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define MAXN 5005
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second

const int inf = 2 * 1e18;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  set<pii> st;
  st.insert({{0, inf}, 0});
  auto dale = [&](int l, int r, int c, int ll, int rr, int to_add)
  {
    st.erase({{l, r}, c});
    if (l < ll)
    {
      st.insert({{l, ll - 1}, c});
    }
    if (r > rr)
    {
      st.insert({{rr + 1, r}, c});
    }
    int cc = c + to_add;
    if (ll == l)
    {
      while (1)
      {
        auto it = st.lower_bound({{ll, ll}, -1});
        if (it == st.begin())
          break;
        it--;
        if ((*it).sec == cc)
          ll = min(ll, (*it).fir.fir), st.erase(*it);
        else
          break;
      }
    }
    if (rr == r)
    {
      while (1)
      {
        auto it = st.lower_bound({{ll, rr}, (int)1e18});
        if (it == st.end())
          break;
        if ((*it).sec == cc)
          rr = max(rr, (*it).fir.sec), st.erase(*it);
        else
          break;
      }
    }
    st.insert({{ll, rr}, cc});
  };
  for (int i = 0; i < n; i++)
  {
    char c;
    int a, b;
    cin >> c >> a >> b;
    if (c == '|')
    {
      auto it = st.lower_bound({{b + 1, b + 1}, -1});
      it--;
      int l = (*it).fir.fir;
      int r = (*it).fir.sec;
      int c = (*it).sec;
      dale(l, r, c, b, b, a);
      cout << "S";
    }
    else
    {
      auto it = st.lower_bound({{b + a, b + a}, -1});
      it--;
      int l = (*it).fir.fir;
      int r = (*it).fir.sec;
      int c = (*it).sec;
      if (l <= b && r >= (b + a - 1))
      {
        cout << "S";
        dale(l, r, c, b, b + a - 1, 1);
      }
      else
      {
        cout << "U";
      }
    }
  }
  cout << endl;
  return 0;
}