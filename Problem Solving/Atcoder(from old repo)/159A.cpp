#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int n, m;
  cin >> n >> m;
 
  double c1 = (n * (n - 1)) / 2;
  double c2 = (m * (m - 1)) / 2;
 
  cout << c1 + c2 << endl;
  return 0;
}
