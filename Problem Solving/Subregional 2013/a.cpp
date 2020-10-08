#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define double long double
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000001
#define MAXL 20
#define mod 998244353

signed main()
{
  vector<int> v(3);
  int m0 = -1, m1 = -1;
  for (int i = 0; i < 3; i++)
  {
    cin >> v[i];
    if (v[i] == 0 && m0 == -1)
      m0 = i;
    else if (v[i] == 0 && m0 != -1)
      m0 = -2;
    else if (v[i] == 1 && m1 == -1)
      m1 = i;
    else if (v[i] == 1 && m1 != -1)
      m1 = -2;
  }
  char aux;
  if (m1 == -1 || m0 == -1)
    cout << "*" << endl;
  else if (m0 != -2)
    aux = m0 + 'A', cout << aux << endl;
  else
    aux = m1 + 'A', cout << aux << endl;
  return 0;
}