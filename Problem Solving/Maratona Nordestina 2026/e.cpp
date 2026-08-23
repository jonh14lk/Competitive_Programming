#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 2005
#define mod 998244353

char qry(int l, int len)
{
  cout << "? " << len << " ";
  for (int i = l; i < (l + len + len); i++)
    cout << i << " ";
  cout << endl;
  cout.flush();
  char ans;
  cin >> ans;
  return ans;
}
void solve(int l, int r)
{
  if (l == r)
  {
    cout << "! " << l << endl;
    cout.flush();
    exit(0);
  }
  int len = (r - l + 1) / 3;
  len = max(len, 1ll);
  char c = qry(l, len);
  if (c == 'E')
    return solve(l, l + len - 1);
  else if (c == 'D')
    return solve(l + len, l + len + len - 1);
  else
    return solve(l + len + len, r);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  solve(1, n);
  return 0;
}