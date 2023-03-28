#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int n, h, w;
  cin >> n >> h >> w;
  while (n--)
  {
    char a, b;
    cin >> a >> b;
    if (a == 'Y')
    {
      w++;
      h--;
      cout << "Y ";
    }
    else if (w == 0)
    {
      w++;
      h--;
      cout << "Y ";
    }
    else
    {
      cout << "N ";
    }

    if (b == 'Y')
    {
      w--;
      h++;
      cout << "Y ";
    }
    else if (h == 0)
    {
      w--;
      h++;
      cout << "Y ";
    }
    else
    {
      cout << "N ";
    }
    cout << endl;
  }
}