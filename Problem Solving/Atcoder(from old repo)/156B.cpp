#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define lli long long int
 
int main ()
{   
    ios_base::sync_with_stdio(false) ;
    cin.tie(NULL) ;
 
    int n , k ;
    cin >> n >> k ;
    int ans = 0 ;
 
    for (int i = 1 ; i <= n ; i++)
    {
        int at = pow(k , i) ;
        
        if (at <= n)
        {
            ans = i ;
        }
        else 
        {
            ans = i ;
            break ;
        }
    }
 
    cout << ans << endl ;
    
    return 0;
}
