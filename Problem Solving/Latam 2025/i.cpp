#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  set<int> s;
  map<int, int> mp;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    mp[x]++;
    s.insert(x);
  }
  for (auto const &i : mp)
  {
    if (i.sec % 2 == 0)
      s.erase(i.fir);
  }
  if (s.size() == 0 || s.size() == 1)
  {
    cout << "E\n";
  }
  else
  {
    if (s.size() % 2 == 0)
      cout << "F\n";
    else
      cout << "S\n";
  }
  return 0;
}