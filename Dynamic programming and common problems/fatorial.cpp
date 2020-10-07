#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 10000000
#define mod 1000000007

lli dp[MAXN] ;

void fat ()
{
    dp[0] = 1 ;

    for (int i = 1 ; i < MAXN ; i++)
    {
        dp[i] = (dp[i - 1] % mod * i % mod) % mod ;
    }
}
int main()
{
    fat () ;
    lli n ;
    cin >> n ;
    cout << dp[n] << endl ;
}