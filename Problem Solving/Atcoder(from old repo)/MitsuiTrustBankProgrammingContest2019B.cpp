#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define im (int i = 0 ; i < m ; i++)
#define jx (int j = 0 ; j < x ; j++)
#define kn (int k = 0 ; k < n ; k++)
#define ln (int l = 0 ; l < n ; l++)
#define wq while (q--)
 
 
int main ()
{
    double n ;
    cin >> n ;
 
    double aux = n / 1.08 ;
    int aux2 = ceil(aux);
 
    if (floor ((double) aux2 * 1.08)  == n)
    {
        cout << aux2 << endl ;
    }
    else
    {
        cout << ":(" << endl ;
    }
    
      
    return 0 ;
}
