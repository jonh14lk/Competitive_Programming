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
#define MAXN 100005
#define mod 998244353

const int inf = 1e18;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  map<string, int> mp;
  vector<string> str(n);
  vector<pi> coord(n);
  for (int i = 0; i < n; i++)
  {
    string s;
    int x, y;
    cin >> s >> x >> y;
    coord[i] = {x, y};
    mp[s] = i;
    str[i] = s;
  }
  int m;
  cin >> m;
  vector<string> v(m);
  for (int i = 0; i < m; i++)
  {
    cin >> v[i];
  }
  int q, k;
  cin >> q >> k;
  while (q--)
  {
    int f;
    cin >> f;
    vector<string> qq(f);
    for (int i = 0; i < f; i++)
    {
      cin >> qq[i];
    }
    pi best = {-inf, -inf};
    for (int kk = k; kk >= 1; kk--)
    {
      vector<int> cand;
      int l = f - kk;
      for (int a = 0; a + kk < m; a++)
      {
        bool ok = 1;
        for (int i = 0; i < kk; i++)
        {
          ok &= (qq[l + i] == v[a + i]);
        }
        if (ok)
        {
          cand.pb(a + kk);
        }
      }
      if (cand.size() > 0)
      {
        for (int i = 0; i < n; i++)
        {
          int curr = 0;
          for (auto const &j : cand)
          {
            if (mp.find(v[j]) != mp.end())
            {
              int id = mp[v[j]];
              curr += (coord[i].fir * coord[id].fir + coord[i].sec * coord[id].sec);
            }
          }
          best = max(best, pi(curr, -i));
        }
        break;
      }
    }
    for (int i = 0; i < f; i++)
    {
      cout << qq[i] << " ";
    }
    if (best.sec == -inf)
      cout << "*\n";
    else
      cout << str[-best.sec] << endl;
  }
  return 0;
}