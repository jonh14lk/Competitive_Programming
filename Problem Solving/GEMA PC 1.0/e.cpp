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
#define MAXN 1001

vector<lli> v;
vector<lli> v2;
lli n, m;

bool possible(lli x)
{
  int j = 0;
  for (int i = 0; i < n; i++)
  {
    while (1)
    {
      if (v2[j] - x <= v[i] && v2[j] >= v[i])
        break;
      else if (v2[j] + x >= v[i] && v2[j] <= v[i])
        break;
      else if (j == m - 1)
        return false;
      else
        j++;
    }
  }
  return true;
}
lli bb()
{
  lli i = 0, f = INT_MAX, m;
  while (i < f)
  {
    m = (i + f) / 2;
    if (possible(m))
    {
      f = m;
    }
    else
    {
      i = m + 1;
    }
  }
  return i;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  v.resize(n);
  v2.resize(m);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < m; i++)
    cin >> v2[i];
  sort(v.begin(), v.end());
  sort(v2.begin(), v2.end());
  cout << bb() << endl;
  return 0;
}