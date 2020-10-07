#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    std::cin.tie(NULL) ;
    
    lli n , mod , a ;
    cin >> n >> mod ;
    
    if (n > mod)
    {
        cout << "0\n";
        return 0 ;
    }
    
    vector <int> v ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> a ;
        v.pb(a);
    }
 
    lli ans = 1 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = i + 1 ; j < n ; j++)
        {
            ans = ((ans % mod) * (abs(v[i] - v[j]) % mod)) % mod ;
            
            if (ans == 0)
            {
                cout << "0\n" ;
                return 0 ;
            }
        }
    }
 
    cout << ans << endl ;
 
    return 0 ;
}
