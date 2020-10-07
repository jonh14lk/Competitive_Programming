#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 2000011

signed main()
{
  int q;
  cin >> q;
  for (int c = 1; c <= q; c++)
  {
    cout << "Case #" << c << ": ";
    string s;
    cin >> s;

    int cof = s[0] - '0';
    for (int i = 0; i < cof; i++)
    {
      cout << "(";
    }
    cout << s[0];

    for (int i = 1; i < s.size(); i++)
    {
      int at = s[i] - '0';
      int att = s[i - 1] - '0';
      int dif = at - att;

      if (dif > 0)
      {
        while (1)
        {
          if (dif == 0)
          {
            break;
          }
          cout << "(";
          dif--;
          cof++;
        }
      }
      else if (dif < 0)
      {
        while (1)
        {
          if (dif == 0)
          {
            break;
          }
          cout << ")";
          dif++;
          cof--;
        }
      }
      cout << s[i];
    }
    while (cof--)
    {
      cout << ")";
    }
    cout << endl;
  }
  return 0;
}