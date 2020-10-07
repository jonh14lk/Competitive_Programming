#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v ;
vector <int> v2 ;
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    lli n , m , p , a ;
    cin >> n >> m >> p ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> a ;
        v.pb(a);
    }
 
    for (int i = 0 ; i < m ; i++)
    {
        cin >> a ;
        v2.pb(a);
    }
 
    lli i = 0 , j = 0 , ans = 0 ;
 
    while (1)
    {
        
        if (v[i] % p == 0 && i < n)
        {
            i++ ;
            ans++ ;
        }
        else 
        {
            break ;
        }
    }   
 
    while (1)
    {
        if (v2[j] % p == 0 && j < m)
        {
            j++ ;
            ans++ ;
        }
        else 
        {
            break ;
        }
    }   
 
    cout << ans << endl ;
 
    return 0 ;
}
