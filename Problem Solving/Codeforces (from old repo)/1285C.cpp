#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
lli gcd (lli x , lli y)
{
    if(x % y == 0)
    {
        return y ;
    }
    else
    {
        return gcd (y , x % y) ;
    }
}
int main()
{
    lli x ;
    cin >> x ;
   
    for (lli i = sqrt(x) ; i >= 1 ; i--)
    {
        if(x % i == 0 && gcd(x / i , i) == 1)
        { 
            printf("%lld %lld\n", i , x / i) ;
            break ;
        }
    }
}
