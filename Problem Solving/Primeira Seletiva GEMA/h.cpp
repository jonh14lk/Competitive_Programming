#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<string> v;
  auto generates = [&](string s, string t)
  {
    if (s.size() != t.size())
      return false;
    for (int i = 0; i <= s.size(); i++)
    {
      rotate(s.begin(), s.begin() + 1, s.end());
      if (s == t)
        return true;
    }
    return false;
  };
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    bool ok = false;
    for (auto const &t : v)
    {
      if (generates(s, t))
      {
        ok = true;
        break;
      }
    }
    if (!ok)
      v.push_back(s);
  }
  cout << v.size() << endl;
}