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
        lli a , b ;
        cin >> a >> b ;
 
        if (a == b)
        {
            cout << "0\n" ;
        }
        else if (a > b && (a - b) % 2 != 0)
        {
            cout << "2\n";
        }
        else if (a > b && (a - b) % 2 == 0)
        {
            cout << "1\n" ;
        }
        else if (a < b && (b - a) % 2 != 0)
        {
            cout << "1\n";
        }
        else if (a < b && (b - a) % 2 == 0)
        {
            cout << "2\n" ;
        }
        
    }
 
    return 0 ;
}
