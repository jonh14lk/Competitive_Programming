#include <bits/stdc++.h>
using namespace std;

#define int long long int

int n, k, e;

int solve(int a, int b)
{
  vector<bool> vis(n + 1, 0);
  vis[k] = 1;
  int ans = a + b;
  for (int i = 1; i <= n; i++)
  {
    if (i > a || vis[i])
    {
      continue;
    }

    vis[i] = 1;

    { // preencher com 1
      int curr = a - i;
      ans = min(ans, curr + b);
      for (int x = 1; x <= n; x++)
      {
        int aa = x;
        int bb = b - x;
        if (bb < 0)
          break;
        if (vis[aa] || vis[bb] || aa == bb)
          continue;
        ans = min(ans, curr);
        break;
      }
    }

    for (int j = 1; j <= n; j++)
    {
      if (i + j > a || vis[j])
        continue;
      vis[j] = 1;
      { // preencher com 2
        int curr = a - (i + j);
        ans = min(ans, curr + b);
        for (int x = 1; x <= n; x++)
        {
          int aa = x;
          int bb = b - x;
          if (bb < 0)
            break;
          if (vis[aa] || vis[bb] || aa == bb)
            continue;
          ans = min(ans, curr);
          break;
        }
      }
      vis[j] = 0;
    }

    vis[i] = 0;
  }
  return ans;
}
signed main()
{
  cin >> n >> k >> e;
  int a = e;
  int b = n - (e + k);
  if (a != k && b != k && a != b)
  {
    cout << "0\n";
    return 0;
  }
  int ans = min(solve(a, b), solve(b, a));
  cout << ans << endl;
}
// preencher um dos lados com 1 ou dois blocos