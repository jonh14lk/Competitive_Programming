#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<int> last(n, -1);
  vector<int> ans(n, 0);
  while (m--)
  {
    int i;
    cin >> i;
    i--;
    if (last[i] != -1)
    {
      ans[last[i]]++;
      last[last[i]] = i;
    }
    else
    {
      ans[(i + 1) % n]++;
      last[(i + 1) % n] = i;
    }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << " ";
  cout << endl;
}
