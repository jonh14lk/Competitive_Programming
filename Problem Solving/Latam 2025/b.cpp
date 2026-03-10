#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  set<pair<int, int>> s;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    s.insert({v[i], i});
  }
  vector<pair<int, int>> ans;
  auto op = [&](int i, int j)
  {
    ans.push_back({i + 1, j + 1});
    int sum = v[i] + v[j];
    v[i] = sum / 2;
    v[j] = (sum + 1) / 2;
  };
  for (int i = 0; (i + 1) < n; i++)
  {
    s.erase({v[i], i});
    while (true)
    {
      int j = (*s.begin()).second;
      if (v[i] <= v[j])
        break;
      s.erase({v[j], j});
      op(i, j);
      s.insert({v[j], j});
    }
  }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
  {
    cout << ans[i].first << " " << ans[i].second << endl;
  }
  return 0;
}