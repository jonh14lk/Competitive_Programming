
#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int n;
  cin >> n;
  multiset<int> s;
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    sum += x;
    s.insert(x);
    if (sum < 0)
    {
      sum -= (*s.begin());
      s.erase(s.begin());
    }
  }
  cout << s.size() << endl;
}