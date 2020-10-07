#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
  int l;
  cin >> l;
  double ans;
  double k = (double)l / 3;
  ans = k * k * k;
  printf("%.12lf\n", ans);
  return 0;
}
