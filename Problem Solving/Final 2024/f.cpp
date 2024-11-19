#include <bits/stdc++.h>
using namespace std;

bool check(string &s)
{
  int n = s.size();
  for (int i = 0; i < n; i++)
  {
    bool ok = (s[i] == 'X');
    if (i - 1 >= 0 && s[i - 1] == 'X')
      ok = 1;
    if (i + 1 < n && s[i + 1] == 'X')
      ok = 1;
    if (!ok)
      return 0;
  }
  return 1;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int a, b;
  cin >> a >> b;
  int qt = (b + 2) / 3;
  for (int ini = 0; ini <= 1; ini++)
  {
    if (b == 1 && ini == 1)
    {
      break;
    }
    string s(b, '-');
    int ptr = ini;
    bool ok = 1;
    for (int i = 0; i < a; i++)
    {
      if (ptr >= b)
      {
        ok = 0;
        break;
      }
      s[ptr] = 'X';
      int rem = a - (i + 1);
      int len = b - (ptr + 3);
      int to_put = (len + 2) / 3;
      if (to_put >= rem)
      {
        ptr += 3;
      }
      else
      {
        ptr += 2;
      }
    }
    if (ok && check(s))
    {
      cout << s << endl;
      return 0;
    }
  }
  cout << "*\n";
}
// 3 em 3
// mas pode ser de 2 em 2