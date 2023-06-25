#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, q;
  string s;
  cin >> n >> q >> s;
  int ptr = 0;
  while (q--)
  {
    int t, x;
    cin >> t >> x;
    if (t == 1)
      ptr = (ptr + n - x) % n;
    else
      cout << s[(ptr + x - 1) % n] << endl;
  }
}