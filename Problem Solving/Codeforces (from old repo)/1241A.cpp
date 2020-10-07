#include <bits/stdc++.h>
using namespace std ;
 
void loop (int i , int n)
{
    if (i < n)
    {
        long long int num ;
        scanf("%lld", &num);
 
        if (num == 2) printf("2\n");
        else if (num % 2 != 0) printf("1\n");
        else printf("0\n");
 
        loop (i + 1 , n);
    }
}
int main() 
{
    int n ;
    scanf("%d", &n);
 
    loop (0 , n);
    return 0;
}
