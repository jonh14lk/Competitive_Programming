#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define MAXN 1505
#define pi pair<int, int>
#define fir first
#define sec second

const int inf = 1000000008;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, p, h;
  cin >> n >> p >> h;
  int at = 0;
  vector<int> sums, mults;
  for (int i = 0; i < n; i++)
  {
    char c;
    cin >> c;
    if (c == '*')
    {
      int x;
      cin >> x;
      if (x > 1)
        mults.pb(x);
    }
    else if (c == '+')
    {
      int x;
      cin >> x;
      sums.pb(x);
    }
    else
    {
      at++;
    }
  }
  if (at == 0)
  {
    cout << "*\n";
    return 0;
  }
  int last = 0, ans = 0, resp = 1e18, r;
  sort(sums.rbegin(), sums.rend());
  sort(mults.rbegin(), mults.rend());
  for (int turn = 0; turn < 60; turn++)
  {
    int pp = p;
    for (auto const &i : sums)
    {
      pp += i;
      if (pp > h)
        break;
    }
    for (auto const &i : mults)
    {
      if (pp > h)
        break;
      pp *= i;
      if (pp > h)
        break;
    }
    int dale = min(pp, inf) * at;
    if (dale >= h)
    {
      // aqui tenho que brutar e dale
      for (int i = 0; i <= sums.size(); i++)
      {
        for (int j = 0; j <= mults.size(); j++)
        {
          for (int k = 1; k <= at; k++)
          {
            int curr = p;
            for (int x = 0; x < i; x++)
            {
              curr += sums[x];
              curr = min(curr, inf);
            }
            for (int x = 0; x < j; x++)
            {
              curr *= mults[x];
              curr = min(curr, inf);
            }
            int seila = curr * k;
            if (seila >= h)
              resp = min(resp, ans + i + j + k);
          }
        }
      }
      cout << resp << endl;
      return 0;
    }
    ans += n;
    h -= dale;
    r = pp - p;
    p = pp;
    if (h == last)
    {
      cout << "*\n";
      return 0;
    }
    last = h;
  }
  p += r;
  auto can = [&](int x)
  {
    __int128 seila = (__int128)2 * (__int128)p + (__int128)(x - 1) * (__int128)r;
    seila *= x;
    seila /= 2;
    seila *= at;
    return seila >= h;
  };
  // cout << p << " " << h << " " << ans<< endl;
  int lo = 1, hi = inf;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    (can(mid)) ? hi = mid : lo = mid + 1;
  }
  if ((lo - 1) > 0)
  {
    __int128 seila = (__int128)2 * (__int128)p + (__int128)(lo - 2) * (__int128)r;
    seila *= (lo - 1);
    seila /= 2;
    seila *= at;
    ans += (lo - 1) * n;
    p = (lo - 2) * r + p;
    h -= seila;
  }
  // cout << p << " " << h << " " << ans<< endl;
  //  aqui tenho que brutar e dale
  for (int i = 0; i <= sums.size(); i++)
  {
    for (int j = 0; j <= mults.size(); j++)
    {
      for (int k = 1; k <= at; k++)
      {
        int curr = p;
        for (int x = 0; x < i; x++)
        {
          curr += sums[x];
          curr = min(curr, inf);
        }
        for (int x = 0; x < j; x++)
        {
          curr *= mults[x];
          curr = min(curr, inf);
        }
        int seila = curr * k;
        if (seila >= h)
          resp = min(resp, ans + i + j + k);
      }
    }
  }
  cout << resp << endl;
  return 0;
}