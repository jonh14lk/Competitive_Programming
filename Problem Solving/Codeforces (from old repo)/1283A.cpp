#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int n ;
    cin >> n ;
 
    while (n--)
    {
        int a , b ;
        cin >> a >> b ;
 
        int t = (a * 60 ) + b ;
 
        cout << 1440 - t << endl ;
    }
 
    return 0 ;
}
