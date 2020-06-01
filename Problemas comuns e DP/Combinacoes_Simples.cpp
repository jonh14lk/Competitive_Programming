#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 100000
#define mod 998244353

lli dp[MAXN] ;

void fat ()
{
    dp[0] = 1 ;

    for (int i = 1 ; i < MAXN ; i++)
    {
        dp[i] = (dp[i - 1] % mod * i % mod) % mod ;
    }
}
lli binpow (lli x , lli y)
{
    lli z = 1 ;

    while (y)
    {
        if (y & 1) 
        {
            z = (z * 1ll * x) % mod ;
        }

        x = (x * 1ll * x) % mod ;
        y >>= 1 ;
    }

    return z ;
}
lli inverso (lli x) 
{
    return binpow (x , mod - 2) ;
}
lli divisao (lli x , lli y) 
{
    return (x * 1ll * inverso(y)) % mod ;
}
lli multipicacao (lli x , lli y) 
{
    return (x * 1ll * y) % mod ;
}
lli combinacao (lli n , lli k)
{
    lli denominador = multipicacao(dp[k] , dp[n - k]) ;
    lli ans = divisao(dp[n]  , denominador) ;
    return ans ;
}
int main()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
    fat();
    lli n , m ;
    cin >> n >> m ;
    cout << combinacao (n , m) << endl ;
}
