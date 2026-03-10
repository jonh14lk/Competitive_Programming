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
  int n, x, k;
  cin >> n >> x >> k;
  x++;
  vector<int> v(n);
  vector<bool> disc(n, 0);
  int cnt = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    cnt++;
    if (cnt == x)
    {
      disc[i] = 1;
      cnt = 0;
    }
  }
  multiset<int> s;
  int ptr = n - 1, ans = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    while (ptr >= 0 && (ptr + k) >= i)
    {
      s.insert(v[ptr]);
      ptr--;
    }
    if (disc[i])
    {
      int x = *s.rbegin();
      ans += x / 2;
      s.erase(s.find(x));
    }
    else
    {
      int x = *s.begin();
      s.erase(s.find(x));
    }
  }
  cout << ans << endl;
  return 0;
}