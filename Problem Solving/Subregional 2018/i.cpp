#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXL 20
#define MAXN 1001

int lampada[MAXN];
int matrix[MAXN][MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k, l, a, ans = 0;
  cin >> k >> l >> a;
  for (int i = 1; i <= a; i++)
  {
    int n;
    cin >> n;
    lampada[n] = 1;
  }
  for (int i = 1; i <= k; i++)
  {
    cin >> a;
    for (int j = 1; j <= a; j++)
    {
      int n;
      cin >> n;
      matrix[i][n] = 1;
    }
  }
  bool canzona = true;
  for (int p = 1; p <= l; p++)
    if (lampada[p] == 1)
      canzona = false;
  if (!canzona)
  {
    for (int i = 1; i <= 2; i++)
    {
      for (int j = 1; j <= k; j++)
      {
        ans++;
        for (int p = 1; p <= l; p++)
          lampada[p] = (lampada[p] + matrix[j][p]) % 2;
        bool can = true;
        for (int p = 1; p <= l; p++)
          if (lampada[p] == 1)
            can = false;
        if (can)
        {
          cout << ans << endl;
          return 0;
        }
      }
    }
    cout << "-1\n";
  }
  else
  {
    cout << ans << endl;
  }
  return 0;
}
