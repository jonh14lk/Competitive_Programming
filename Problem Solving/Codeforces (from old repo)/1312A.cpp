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
        int n , m ;
        cin >> n >> m ;
 
        if (n % m == 0 && m >= 3)
        {
            cout << "YES\n" ;
        }
        else
        {
            cout << "NO\n" ;
        }
    }
 
    return 0 ;
}
