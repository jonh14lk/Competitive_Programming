#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int c, n;
  cin >> c >> n;
  vector<int> v(n);
  vector<int> vals;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    vals.pb(v[i]);
  }
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());
  auto can = [&](int x)
  {
    int sq = 0;
    for (auto const &i : v)
    {
      if (i >= x)
        sq = 0;
      else
        sq++;
      if (sq > c)
        return 0;
    }
    return 1;
  };
  int l = 0, r = vals.size() - 1;
  while (l < r)
  {
    int mid = (l + r + 1) >> 1;
    (can(vals[mid])) ? l = mid : r = mid - 1;
  }
  cout << vals[l] << endl;
  return 0;
}