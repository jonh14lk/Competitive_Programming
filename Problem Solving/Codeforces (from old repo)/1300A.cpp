#include <bits/stdc++.h>
using namespace std ;
 
#define pb push_back
#define lli long long int
 
int main ()
{
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n , aux ;
        lli sum = 0 ;
        lli ans = 0 ;
        cin >> n ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> aux ;
 
            if (aux == 0)
            {
                ans++ ;
                aux = 1 ;
            }
 
            sum += aux ;
        }
 
        if (sum == 0)
        {
            ans += 1 ;
        }
 
        cout << ans << endl ;
 
    }
 
    return 0 ;
}
