#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 2000011

signed main()
{
  int q;
  cin >> q;
  for (int c = 1; c <= q; c++)
  {
    cout << "Case #" << c << ": ";
    int n;
    cin >> n;
    vector<pi> v;
    vector<pi> m;
    vector<bool> visited;
    for (int i = 0; i < n; i++)
    {
      int a, b;
      cin >> a >> b;
      v.pb(mp(a, b));
      m.pb(mp(a, b));
      visited.pb(false);
    }
    sort(v.begin(), v.end());
    vector<char> ans(n);
    bool can = true;
    int tc = 0, tj = 0;
    for (int i = 0; i < n; i++)
    {
      if (tc <= v[i].fir)
      {
        for (int j = 0; j < n; j++)
        {
          if (m[j].fir == v[i].fir && m[j].sec == v[i].sec && !visited[j])
          {
            ans[j] = 'C';
            tc = v[i].sec;
            visited[j] = true;
            break;
          }
        }
      }
      else if (tj <= v[i].fir)
      {
        for (int j = 0; j < n; j++)
        {
          if (m[j].fir == v[i].fir && m[j].sec == v[i].sec && !visited[j])
          {
            ans[j] = 'J';
            tj = v[i].sec;
            visited[j] = true;
            break;
          }
        }
      }
      else
      {
        can = false;
      }
    }
    if (!can)
    {
      cout << "IMPOSSIBLE" << endl;
    }
    else
    {
      for (int i = 0; i < ans.size(); i++)
      {
        cout << ans[i];
      }
      cout << endl;
    }
  }
  return 0;
}