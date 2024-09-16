#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pi pair<int, int>
#define pb push_back
#define fir first
#define sec second

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<string> s(2);
  cin >> s[0] >> s[1];
  vector<pi> aux;
  for (int i = 0; i < 2; i++)
  {
    reverse(s[i].begin(), s[i].end());
    for (int j = 0; j < s[i].size(); j++)
    {
      if (s[i][j] == '*')
        aux.pb({i, j});
    }
  }
  int x = aux.size();
  for (int mask = 0; mask < (1 << x); mask++)
  {
    vector<string> v = s;
    int cc = 0;
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < v[i].size(); j++)
      {
        if (v[i][j] == '*')
        {
          char curr = (mask & (1 << cc)) ? '1' : '0';
          v[i][j] = curr;
          cc++;
        }
      }
    }
    int num = 0;
    for (int j = 0; j < v[1].size(); j++)
    {
      if (v[1][j] == '1')
        num |= (1 << j);
    }
    if (num == 0)
    {
      continue;
    }
    int pot = 1, x = 0;
    for (int j = 0; j < v[0].size(); j++)
    {
      if (v[0][j] == '1')
        x = (x + pot) % num;
      pot = (pot * 2) % num;
    }
    if (x == 0)
    {
      reverse(v[0].begin(), v[0].end());
      cout << v[0] << endl;
      exit(0);
    }
  }
  return 0;
}