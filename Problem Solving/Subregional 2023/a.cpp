#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n, h;
  cin >> n >> h;
  int cnt = 0;
  for (int i = 0; i < n; i++)
  {
    int ch;
    cin >> ch;
    cnt += (ch <= h);
  }
  cout << cnt << endl;
}