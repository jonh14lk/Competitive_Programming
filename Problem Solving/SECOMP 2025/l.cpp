#include <bits/stdc++.h>
using namespace std;

#define int long long int

string s, curr;

void solve(int i)
{
  if (i == s.size())
  {
    cout << curr << endl;
    return;
  }
  {
    curr.push_back(tolower(s[i]));
    solve(i + 1);
    curr.pop_back();
  }
  if (i + 1 < s.size() && s[i] == 'S' && s[i + 1] == 'S')
  {
    curr.push_back('B');
    solve(i + 2);
    curr.pop_back();
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s;
  solve(0);
  return 0;
}