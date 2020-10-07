#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int a , b ;
    cin >> a >> b ;
 
    int n = 1 ;
    n = 1 ;
 
    while (n <= 1000000)
    {
        double r = (double) n * 0.08 ;
        double r2 = (double) n * 0.1 ;
        int r3 = floor(r) ;
        int r4 = floor(r2);
     
        if (r3 == a && r4 == b)
        {
            cout << n << endl ;
            return 0 ;
        }
        
 
        n++ ;
    }
  
    cout << "-1\n" ; 
 
    
    return 0 ;
}
