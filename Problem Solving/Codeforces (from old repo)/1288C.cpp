#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define MAXN 2000
#define mod 1000000007
 
lli dp [MAXN][MAXN];
 
void solve (int n , int m)
{
    dp[0][0] = 1 ;
 
    for (int i = 1 ; i <= n ; i++)
    {
        dp[i][0] = 1 ;
 
        for (int j = 1 ; j <= m ; j++)
        {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod ;
        }   
    }
 
    cout << dp[n][m] << endl ;
}
int main()
{
    lli n , m ;
    cin >> n >> m ;
    solve(n + 2 * m - 1 , 2 * m);
 
    return 0 ;
}
