#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n , m , a ;
        cin >> n >> m ;
 
        vector <int> v ;
        lli at_sum = 0 ;
        lli ot_sum = 0 ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> a ;
            at_sum += a ;
 
            if (i != 0)
            {
                ot_sum += a ;
            }
 
            v.pb(a);
        }
 
        int need = m - v[0] ;
 
        if (need <= ot_sum)
        {
            cout << m << endl ;
        }
        else
        {
            cout << v[0] + ot_sum << endl ;
        }
        
 
    }
 
    return 0 ;
}
