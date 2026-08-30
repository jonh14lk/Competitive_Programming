#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  int r = n, c = m;
  vector<string> v(n);
  vector<string> v2(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    v2[i] = v[i];
  }
  auto rotate90 = [&]()
  {
    vector<string> aux(c, string(r, '.'));
    for (int i = 0; i < r; i++)
    {
      for (int j = 0; j < c; j++)
        aux[j][r - 1 - i] = v2[i][j];
    }
    swap(r, c);
    swap(aux, v2);
  };
  auto vira = [&]()
  {
    for (auto &i : v2)
      reverse(i.begin(), i.end());
  };
  auto check = [&]()
  {
    if (n != r || m != c)
      return 0;
    for (int i = 0; i < r; i++)
    {
      for (int j = 0; j < c; j++)
      {
        if (v[i][j] != v2[i][j])
          return 0;
      }
    }
    return 1;
  };
  int ans = 0;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      rotate90();
      if (check())
        ans++;
    }
    vira();
  }
  cout << ans << endl;
  return 0;
}