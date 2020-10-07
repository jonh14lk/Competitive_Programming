#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    int q ;
    cin >> q ;
 
    while(q--)
    {
        lli a , b ;
        cin >> a >> b ;
        lli ai = 0  , ai2 = 9 ;
 
        while (1)
        {
            if (b >= ai2)
            {
                ai++ ;
                ai2 = (ai2 * 10) + 9 ;
            }
            else
            {
                break ;
            }
        }
 
        cout << a * ai << endl ;
    }
 
    return 0;
}
