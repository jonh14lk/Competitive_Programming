#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jm (int j = 0 ; j < m ; j++)
 
int main ()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
 
    lli a , b , x ;
    scanf("%lld%lld%lld", &a , &b , &x);
    
    lli i = 0 ;
    lli x2 = x ;
    int aux ;
 
    while (x2 > 0)
    {
        aux = x2 % 10 ;
        x2 = x2 / 10 ;
        i++ ;
    }
 
    lli res = 0 ;
 
    while (1)
    {
        lli n = (x - (b * i)) / a ;
 
        int d = 0 ;
        int i2 = n ;
 
        while (i2 > 0)
        {
            aux = i2 % 10 ;
            i2 = i2 / 10 ;
            d++ ;
        }
 
        if ((a * n) + (b * d) <= x)
        {
            if (n > 1000000000)
            {
                n = 1000000000 ;
            }
            
            res = max(res , n);
        }
        if ((a * n) + (b * d) > x)
        {
            break ;
        }
        
        i-- ;
    }
 
    printf("%lld\n", res);
 
    return 0 ;
}
