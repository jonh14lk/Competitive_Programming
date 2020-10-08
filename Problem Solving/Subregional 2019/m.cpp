#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 100001

lli n, c, t;
lli v[MAXN];

bool possible(lli x)
{
  lli ans = 1, sum = 0;

  for (lli i = 0; i < n; i++)
  {
    if (v[i] > x * t)
    {
      return false;
    }
    else if (sum + v[i] > x * t)
    {
      sum = 0;
      ans++;
      i--;
    }
    else if (sum + v[i] == x * t)
    {
      sum = 0;

      if (i != n - 1)
      {
        ans++;
      }
    }
    else
    {
      sum += v[i];
    }
  }

  return (ans <= c) ? true : false;
}
lli bb()
{
  lli i = 0, f = 1000000000000000, m;

  while (i < f)
  {
    m = (i + f) / 2;

    if (possible(m))
      f = m;
    else
      i = m + 1;
  }

  return i;
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> c >> t;

  for (lli i = 0; i < n; i++)
  {
    cin >> v[i];
  }

  cout << bb() << endl;

  return 0;
}