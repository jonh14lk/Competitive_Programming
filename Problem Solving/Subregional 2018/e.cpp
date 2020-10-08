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
#define MAXL 20
#define MAXN 50500

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string a, b;
  cin >> a >> b;
  int ans = 0, x = 0, y = b.size() - 1;
  while (1)
  {
    if (y == a.size())
      break;
    bool flag = true;
    for (int i = 0; i < b.size(); i++)
    {
      if (b[i] == a[x + i])
      {
        flag = false;
        break;
      }
    }
    if (flag)
      ans++;
    x++;
    y++;
  }
  cout << ans << endl;
  return 0;
}