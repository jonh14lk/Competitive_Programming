#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int r, c;
  cin >> r >> c;
  for (int x = 1; x <= 10; x++)
  {
    for (int y = 1; y <= 10; y++)
    {
      if (x < r && y < c)
      {
        set<int> s;
        s.insert(x * y);
        s.insert((r - x) * y);
        s.insert(x * (c - y));
        s.insert((r - x) * (c - y));
        if (s.size() == 4)
        {
          cout << x << " " << y << endl;
          return 0;
        }
      }
    }
  }
  cout << "*" << endl;
}
