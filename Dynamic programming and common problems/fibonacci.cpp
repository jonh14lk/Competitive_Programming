#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 10000000

lli n , dp[MAXN] ; 

lli fib (lli x)
{ 
    if (dp[x] != -1) 
    {
        return dp[x] ;
    }

    if (x == 0) 
    {
        return 0 ;
    }
    if (x == 1) 
    {
        return 1 ;
    } 

    dp[x] = fib(x - 1) + fib(x - 2) ;

    return dp[x] ;
}
int main ()
{
    memset (dp , -1 , sizeof(dp)) ; 

    cin >> n ;

    cout << fib (n) << endl ; 

    return 0 ;
}
