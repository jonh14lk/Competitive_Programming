nclude <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    lli a , b , c ;
    cin >> a >> b >> c ;
 
    if (c > a)
    {
        c = c - a ;
        a = 0 ;
 
        if (c >= b)
        {
            b = 0 ;
        }
        else if (c < b)
        {
            b = b - c ;
            c = 0 ;
        }
    }
    else if (a >= c)
    {
        a = a - c ;
        c = 0 ;
        b = b ;
    }
    
    printf("%lld %lld\n", a , b);
 
    return 0 ;
}
