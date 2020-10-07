#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    lli n , a , b ;
    cin >> n >> a >> b ;
 
    if (a >= n)
    {
        cout << n << endl ;
    }
    else if ((a + b) > n)
    {
        cout << a << endl ;
    }
    else
    {
        lli cof = n / (a + b) ;
        lli res = n % (a + b) ;
 
        if (res > a)
        {
            res = a ;
        }
 
        lli ans = (cof * a) + res ;
        
        cout << ans << endl ;
    }
    
    return 0 ;
}
