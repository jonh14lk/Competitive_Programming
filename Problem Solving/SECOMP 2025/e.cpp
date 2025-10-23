#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    vector<int> ans;
    for (int b = 2; b <= 16; b++)
    {
      int x = n;
      vector<int> number; // vetor com a representação do número N na base B
      while (x)
      {
        number.push_back(x % b);
        x /= b;
      }
      vector<int> number_rev = number;
      reverse(number_rev.begin(), number_rev.end());
      if (number == number_rev)
        ans.push_back(b);
    }
    if (ans.size() == 0)
    {
      cout << "-1\n";
    }
    else
    {
      for (auto const &x : ans)
        cout << x << " ";
      cout << endl;
    }
  }
  return 0;
}