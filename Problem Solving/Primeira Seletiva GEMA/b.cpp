#include <bits/stdc++.h>
using namespace std;

int main()
{
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++)
      cin >> v[i];
    bool ok = true;
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
      int tot = 0;
      for (int i = 0; i < n; i++)
        tot += count(v[i].begin(), v[i].end(), ch);
      if (tot % n != 0)
        ok = false;
    }
    (ok) ? cout << "YES\n" : cout << "NO\n";
  }
}