#include <bits/stdc++.h>
using namespace std;

int main()
{
  string s, t;
  cin >> s >> t;
  int j = 0;
  for (int i = 0; i < s.size(); i++)
  {
    if (s[i] == t[j])
      j++;
    if (j == t.size())
      break;
  }
  (j == t.size()) ? cout << "YES\n" : cout << "NO\n";
}