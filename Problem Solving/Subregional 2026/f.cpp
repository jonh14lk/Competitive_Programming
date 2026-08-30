#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10000007
#define mod 1000000007

bool vis[MAXN];
int f[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  for (int i = 1; i < MAXN; i++)
  {
    if (vis[i])
      continue;
    int a = i, b = max(i + 1, f[i - 1] + 1);
    vis[a] = 1;
    f[a] = b;
    while (b < MAXN)
    {
      int c = 3 * a;
      vis[b] = 1;
      f[b] = c;
      a = b;
      b = c;
    }
  }
  int n;
  cin >> n;
  cout << f[n] << endl;
  return 0;
}