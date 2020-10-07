#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v ;
int main ()
{
    int n ;
    cin >> n ;
 
    while (n--)
    {
        int k ;
        cin >> k ;
 
        if (k % 2 == 0 && k % 3 == 0)
        {
            continue ;
        }
        else if (k % 2 == 0 && k % 5 == 0)
        {
            continue ;
        }
        else if (k % 2 != 0)
        {
            continue ;
        }
        else
        {
            cout << "DENIED\n" ;
            return 0 ;
        }
        
    }
 
    cout << "APPROVED\n" ;
 
    return 0 ;
} 
