#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
lli mmc(lli num1, lli num2) 
{
    lli mmc, aux, i;
 
    for (i = 1; i <= num2; i++) 
    {
        aux = num1 * i;
        if ((aux % num2) == 0) 
        {
            mmc = aux;
            i = num2 + 1;
        }
    }
    return mmc;
}
int main ()
{
    lli a , b ;
    cin >> a >> b ;
    cout << mmc(a , b) << endl;
    return 0 ;
}
