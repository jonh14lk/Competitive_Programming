#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

bool cmp(vector<int> &a, vector<int> &b)
{
  return (a.size() < b.size());
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> cnt(5, 0);
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    cnt[x % 5]++;
  }
  vector<vector<int>> v;
  for (int i = 0; i < 5; i++)
  {
    int sum = i;
    if (sum % 5 == 0)
      v.pb({i});
    for (int j = 0; j < 5; j++)
    {
      sum = i + j;
      if (sum % 5 == 0)
        v.pb({i, j});
      for (int k = 0; k < 5; k++)
      {
        sum = i + j + k;
        if (sum % 5 == 0)
          v.pb({i, j, k});
        for (int l = 0; l < 5; l++)
        {
          sum = i + j + k + l;
          if (sum % 5 == 0)
            v.pb({i, j, k, l});
          for (int m = 0; m < 5; m++)
          {
            sum = i + j + k + l + m;
            if (sum % 5 == 0)
              v.pb({i, j, k, l, m});
          }
        }
      }
    }
  }
  sort(v.begin(), v.end(), cmp);
  int ans = 0;
  for (auto const &t : v)
  {
    int to_sub = 1e18;
    vector<int> oi(5, 0);
    for (auto &i : t)
    {
      oi[i]++;
    }
    for (int i = 0; i < 5; i++)
    {
      if (oi[i] > 0)
        to_sub = min(to_sub, cnt[i] / oi[i]);
    }
    ans += to_sub;
    for (auto &i : t)
    {
      cnt[i] -= to_sub;
    }
  }
  cout << ans << endl;
  return 0;
}