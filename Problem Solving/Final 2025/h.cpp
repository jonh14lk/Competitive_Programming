#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  int n;
  cin >> n;
  int mx_cur = -1;
  int mx_prv = -1;
  int qtd = 0;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    if (x > mx_cur)
    {
      qtd++;
      mx_cur = x;
    }
    mx_cur = max(mx_cur, x);
  }
  cout << qtd << endl;
}