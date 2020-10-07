#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
bool verify (lli a)
{
    if (a == 0 || a == 1)
    {
        return true ;
    }
    if (a == 2 || a == 3)
    {
        return true ;
    }
    if (a % 2 == 0)
    {
        return false ;
    }
    for (lli i = 3 , end = sqrt(a) ; i <= end; i += 2)
    {
        if(a % i == 0)
        {
            return false ;
        }
    }
 
    return true ;
} 
int main ()
{
    lli a ;
    cin >> a ;
 
    while (1)
    {
        if (verify(a))
        {
            cout << a << endl ;
            return 0 ;
        }
 
        a++;
    }
 
    return 0 ;
}
