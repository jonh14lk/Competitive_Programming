#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define double long double
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000001
#define MAXL 20
#define mod 998244353

signed main()
{
  // a - c == b - a == b - c
  int n;
  cin >> n;
  vector<int> p(n);
  vector<int> v(n);
  set<int> s;
  int dist;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    if (i == 0)
      p[i] = v[i];
    else
      p[i] = p[i - 1] + v[i];
    if (i == n - 1)
      dist = p[i] / 3;
  }
  for (auto const &i : p)
    s.insert(i);
  int ans = 0;
  for (auto const &i : p)
    if (s.find(i + dist) != s.end() && s.find(i + dist + dist) != s.end())
      ans++;
  cout << ans << endl;
  return 0;
}