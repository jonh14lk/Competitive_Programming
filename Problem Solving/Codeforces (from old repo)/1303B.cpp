#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    int q ;
    cin >> q ;
 
    while (q--) 
    {
        lli n , g , b ;
        cin >> n >> g >> b ;
 
        lli gt = 0 ;
        lli bt = 0 ;
        lli wc ;
        lli ans = 0 ;
 
        gt = (n & 1) ? n / 2 + 1 : n / 2 ; 
        bt = n - gt ;
        wc = gt / g - 1 ;
        gt -= wc * g ;
        bt -= wc * b ;
 
        if (gt < 0) 
        {
            gt = 0 ;
        }
        if (bt < 0) 
        {
            bt = 0 ;
        }
 
        ans = wc * (g + b) ;
 
        while (gt) 
        {
            int aux = min (g , gt) ;
 
            ans += aux ; 
            gt -= aux ;
 
            if (gt <= 0) 
            {
                break;
            }
 
            bt -= b ;
 
            if (bt < 0) 
            {
                bt = 0 ;
            }
 
            ans += b ;
        }
 
        ans += bt ;
        cout << ans << endl ;
    }
 
    return 0 ;
}
