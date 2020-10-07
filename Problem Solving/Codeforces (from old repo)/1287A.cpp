#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    int q ;
    string a ;
    int tam , sequence = 0 , maior = 0 ;
 
    cin >> q ;
 
    while (q--)
    {
        cin >> tam ;
        cin >> a ;
        sequence = 0 ;
        maior = 0 ;
 
        for (int i = 0 ; i <= tam ; i++)
        {
            if (a[i] == 'A' && sequence == 0)
            {
                sequence++ ;
            }
            if (a[i] == 'P' && sequence > 0)
            {
                sequence++ ;
            } 
            if (sequence > maior) 
            {
                maior = sequence - 1 ;
            }
            if (a[i] == 'A' && sequence > 0)
            {
                sequence = 1 ;
            }
        }
 
        cout << maior << endl ;
    }
 
    return 0;
}
