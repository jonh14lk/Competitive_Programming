#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    lli n , a , b , c ;
    cin >> n ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> a >> b >> c ;
        cout << (a + b + c) / 2 << endl ;
    }
    
    return 0 ;
}
