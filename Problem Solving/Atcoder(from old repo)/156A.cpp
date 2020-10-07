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
 
    if (n < 10)
    {
        int ans = 100 * (10 - n) ;
        ans += k ;
        cout << ans << endl ;
    }
    else 
    {
        cout << k << endl ;
    }
    
    return 0;
}
