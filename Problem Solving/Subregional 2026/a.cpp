#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007
#define inf 1e9

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> c(n), v(n);
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    c[i] = a;
    v[i] = b;
    if (i > 0)
    {
      c[i] += c[i - 1];
      v[i] += v[i - 1];
    }
  }
  int q;
  cin >> q;
  while (q--)
  {
    int x;
    cin >> x;
    x--;
    int a = c[x] - v[x];
    int b = c[x] + v[x];
    double i = (double)a / b;
    if (i > 0.0)
      cout << "COMPRA\n";
    else if (i < 0.0)
      cout << "VENDA\n";
    else
      cout << "NEUTRO\n";
  }
  return 0;
}