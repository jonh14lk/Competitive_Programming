#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    lli n , a , b ;
    cin >> n ;
 
    while (n--)
    {
        cin >> a >> b ;
 
        lli aux = a / b ;
 
        if (a % b == 0)  cout << a << endl ;
        else if (a % b >= (b / 2)) cout << (aux * b) + (b / 2) << endl ;
        else cout << a << endl ;
        
        
    }
 
    return 0 ;
}
