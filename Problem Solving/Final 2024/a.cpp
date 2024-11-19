#include <bits/stdc++.h>
using namespace std;

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  int n = s.size();
  for (int i = n - 1; i >= 1; i--)
  {
    string t = s.substr(0, i);
    string t2 = s.substr(i, n - i);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    if (t == t2)
    {
      cout << i << endl;
      return 0;
    }
  }
}