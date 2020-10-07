#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    lli q ;
    cin >> q ;
    lli a , b , c , d ;
 
    while (q--)
    {
        cin >> a >> b >> c >> d ;
        lli t = abs(b - a) ;
        
        if (c - d <= min(a , b) && c + d >= max(a , b))
        {
            t = 0 ;
        }
        else if (c + d < min(a , b) || c - d > max(a , b))
        {
            t = t ;
        }
        else if (c - d > min(a , b) && c + d < max(a , b))
        {
            t = t - (2 * d);
        }
        else if(c - d < max(a , b) && c > max(a , b))
        {
            t = t - (max(a , b) - (c - d));
        }
        else if(c + d > min(a , b) && c < min(a , b))
        {
            t = max(a , b) - (c + d)  ;
        }
        else if (c == min (a , b) || c == max (a , b))
        {
            t = t - d ;
        }
        else if (c > max(a , b) && c - d < min(a , b))
        {
            t = 0 ;
        }
        else if (c < min(a , b) && c + d > max(a , b))
        {
            t = 0 ;
        }
        else if (c > min (a , b) && c < max(a , b))
        {
            if (c - d > min(a , b) && c + d >= max(a , b))
            {
                t = t - d ;
                t = t - (max(a , b) - c) ;
            }
            else if (c - d <= min(a , b) && c + d < max(a , b))
            {
                t = t - (c - min(a , b)) ;
                t = t - d ;
 
            }
            else if (c - d > min(a , b) && c + d < max(a , b))
            {
                 t = t - (c - min(a , b)) ;
                 t = t - (max(a , b) - c) ;
 
            }
            else if (c - d <= min(a , b) && c + d >= max(a , b))
            {
                t = 0 ;
            }
        }
        
 
 
        if (t < 0) t = 0 ;
 
 
        cout << t << endl ;
    }
 
    return 0 ;
}
