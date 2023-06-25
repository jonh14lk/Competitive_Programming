#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  while (n--)
  {
    int a, b;
    cin >> a >> b;
    set<int> ans;
    auto factorize = [&](int x)
    {
      for (int i = 2; i * i <= x; i++)
      {
        while (x % i == 0)
        {
          x /= i;
          ans.insert(i);
        }
      }
      if (x > 1)
        ans.insert(x);
    };
    factorize(a);
    factorize(b);
    cout << ans.size() << endl;
  }
}