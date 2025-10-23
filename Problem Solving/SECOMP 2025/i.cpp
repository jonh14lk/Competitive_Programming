#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  if (n == 1)
  {
    cout << "! " << 1 << endl;
    return 0;
  }
  int g = 1;
  vector<int> ans(n + 1, 0);
  for (int i = 2; i <= n; i++)
  {
    cout << "? " << g << " " << i << endl;
    int a;
    cin >> a;
    cout << "? " << i << " " << g << endl;
    int b;
    cin >> b;
    if (a > b)
    {
      ans[g] = a;
      g = i;
    }
    else
    {
      ans[i] = b;
    }
  }
  ans[g] = n;
  cout << "! ";
  for (int i = 1; i <= n; i++)
  {
    cout << ans[i] << " ";
  }
  cout << endl;
  return 0;
}