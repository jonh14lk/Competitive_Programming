
#include <bits/stdc++.h>
using namespace std;

#define int long long int

struct match
{
  int start, end;
};

int read_date()
{
  int a, b;
  char c;
  cin >> a >> c >> b;
  return a * 60 + b;
}
signed main()
{
  int n;
  cin >> n;
  vector<match> v(n);
  for (int i = 0; i < n; i++)
  {
    v[i].start = read_date();
    v[i].end = read_date();
  }
  int ans = 0;
  for (int t = 0; t <= 1440; t++)
  {
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
      if (v[i].start <= t && v[i].end >= t)
        cnt++;
    }
    ans = max(ans, cnt);
  }
  cout << ans << endl;
}