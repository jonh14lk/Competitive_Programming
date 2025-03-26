#include <bits/stdc++.h>
using namespace std;

#define int long long int

string hue[10] = {
    "GGGgGGG",
    "gggggGG",
    "gGGGGGg",
    "ggGGGGG",
    "GggGgGG",
    "GgGGGgG",
    "GGGGGgG",
    "ggGggGG",
    "GGGGGGG",
    "GgGGGGG"};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    string t;
    cin >> t;
    int ans = -1, cnt = 0;
    for (int i = 0; i <= 9; i++)
    {
      bool ok = 1;
      for (int j = 0; j < 7; j++)
      {
        if (t[j] != '+' && t[j] != '-')
          ok &= (t[j] == hue[i][j]);
      }
      if (ok)
      {
        ans = i;
        cnt++;
      }
    }
    if (cnt == 1)
    {
      cout << ans;
    }
    else
    {
      cout << "*";
    }
  }
  cout << endl;
  return 0;
}