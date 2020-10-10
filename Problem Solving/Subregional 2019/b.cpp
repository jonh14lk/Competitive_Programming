#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 11

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int best = 0;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i], best = max(best, v[i]);
  (best == v[0]) ? cout << "S\n" : cout << "N\n";
  return 0;
}