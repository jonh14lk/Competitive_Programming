#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define im (int i = 2 ; i <= 100 ; i++)
#define jx (int j = 0 ; j <= 100 ; j++)
#define kn (int k = 0 ; k <= 100 ; k++)
#define ln (int l = 0 ; l <= 100 ; l++)
#define pn (int p = 0 ; p <= 100 ; p++)
#define wq while (q--)
 
 
int main ()
{
    int n  , a , b ;
    cin >> n ;
    
    if (n < 100)
    {
        printf("0\n");
        return 0 ;
    }
 
    for im
    {
        a = (105 * (i - 1));
        b = i * 100 ;
 
       // cout << a << endl ;
        //cout << b << endl ;
 
        if (n < b && n > a)
        {
            printf("0\n");
            return 0 ; 
        }
    }
 
    printf("1\n");
    return 0 ;
}
