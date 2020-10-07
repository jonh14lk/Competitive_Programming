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
    cout << "Case #" << c << ": " << endl;
    lli n;
    cin >> n;
    if (n == 1)
    {
      cout << 1 << " 1\n";
    }
    else
    {
      cout << 1 << " 1\n";
      cout << 2 << " 2\n";
      lli sum = 2;
      lli next = 1;
      lli increment = 2;
      lli pos = 3;
      while (1)
      {
        if (sum + next > n)
        {
          break;
        }
        else
        {
          sum += next;
          cout << pos << " 3\n";
          pos++;
          next += increment;
          increment++;
        }
      }
      pos--;
      next = pos - 1;
      while (1)
      {
        if (sum + next > n)
        {
          break;
        }
        else
        {
          sum += next;
          cout << pos << " 2\n";
          pos++;
          next++;
        }
      }
      pos--;
      if (n - sum >= 1)
      {
        cout << pos << " " << 1 << endl;
        sum += 1;
      }
      pos++;
      while (1)
      {
        if (sum == n)
        {
          break;
        }
        else
        {
          cout << pos << " " << 1 << endl;
          pos++;
          sum++;
        }
      }
    }
  }
  return 0;
}
