#include <bits/stdc++.h>
using namespace std;
 
int main()
{
  long long int n;
  scanf("%lld", &n);
  
  long long int g = n;
 
  for (long long int i = 2 , end = sqrt(n); i <= end; i ++)
  {
      if (n % i == 0)
      {
        g = gcd(g, i);
        
        if (i != n / i)
        {
            g = gcd(g, n / i);
        }
        
      }
  }
  
  printf("%lld\n", g);
  
  return 0;
}
