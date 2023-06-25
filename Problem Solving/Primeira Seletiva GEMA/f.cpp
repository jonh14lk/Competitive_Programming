#include <bits/stdc++.h>
using namespace std;

#define int long long int // avoid overflow

signed main()
{
  int x;
  cin >> x;
  vector<int> ans;
  set<int> s;
  for (int i = 1; i <= 100005; i++)
  {
    s.insert(i * i);
    if (s.count((i * i) - x))
      ans.push_back(i);
  }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i] << " \n"[i == ans.size() - 1];
}