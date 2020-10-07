#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    int n , i , j;
    scanf("%d", &n);
    long long int matriz [n][n] ;
 
    for (i = 0 ; i < n ; i++)
        for (j = 0 ; j < n ; j++) scanf("%lld", &matriz[i][j]);
    
    long long int a = matriz[0][1] ;
    long long int b = matriz[0][2] ;
    long long int c = matriz[1][2] ;
 
    int zero = sqrt ((a * b) / c);
    printf("%d ", zero);
    
    for (i = 1 ; i < n ; i++) (i == n - 1) ? printf("%lld\n", (matriz[0][i] / zero)): printf("%lld ", (matriz[0][i] / zero));
        
    return 0 ;
}
