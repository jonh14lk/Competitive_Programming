#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define double long double
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN
#define mod 1000000007

string s;
int n, num;

namespace bit
{
  vector<int> bit;

  int sum(int r)
  {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
      ret += bit[r];
    return ret;
  }
  void add(int idx, int delta)
  {
    for (; idx < 2 * n; idx = idx | (idx + 1))
      bit[idx] += delta;
  }
} // namespace bit
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s >> num;
  n = s.size();
  bit::bit.resize(2 * n);
  for (int i = 0; i < 2 * n; i++)
  {
    int curr = (s[i % n] == 'E') ? 1 : 0;
    bit::add(i, curr);
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    int l = i, r = i + num - 1, kappa = i + num - 1;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      (bit::sum(mid) - bit::sum(i - 1)) ? r = mid : l = mid + 1;
    }
    if ((bit::sum(l) - bit::sum(i - 1)))
      ans += (kappa - l + 1);
  }
  cout << ans << endl;
  return 0;
}
// no maximo tamanho = tam
// no minimo um eggfruit