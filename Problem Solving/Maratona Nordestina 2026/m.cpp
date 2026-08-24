#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

int cnt[4];
int v[4];

int calc(int v00, int v01, int v10, int v11)
{
  return (v00 * v11 * -2) + (v01 * v10 * 2) + (v00 * v00) + (v11 * v11) - (v01 * v01) - (v10 * v10);
}
int solve(int i)
{
  if (i == 4)
    return calc(v[0], v[1], v[2], v[3]) + calc(cnt[0] - v[0], cnt[1] - v[1], cnt[2] - v[2], cnt[3] - v[3]);
  int l = 0, r = cnt[i];
  while (l < r)
  {
    int mid = (l + r) >> 1;
    v[i] = mid;
    int v1 = solve(i + 1);
    v[i] = mid + 1;
    int v2 = solve(i + 1);
    (v1 > v2) ? r = mid : l = mid + 1;
  }
  v[i] = l;
  return solve(i + 1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  string s, t;
  cin >> s >> t;
  for (int i = 0; i < n; i++)
  {
    int a = s[i] == 'G';
    int b = t[i] == 'G';
    cnt[a * 2 + b]++;
  }
  cout << solve(0) << endl;
  return 0;
}