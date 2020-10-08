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
  int n, r;
  cin >> n >> r;
  set<int> s;
  for (int i = 1; i <= n; i++)
    s.insert(i);
  for (int i = 0; i < r; i++)
  {
    int k;
    cin >> k;
    s.erase(k);
  }
  if (s.size() == 0)
  {
    cout << "*" << endl;
  }
  else
  {
    for (auto const &i : s)
      cout << i << " ";
    cout << endl;
  }
  return 0;
}