#include <bits/stdc++.h>
using namespace std ;
 
int main() 
{
    int a , b ;
    scanf("%d%d", &a , &b);
 
    if (a <= 9 && b <= 9)
    {
        printf("%d\n", a *b);
    }
    else
    {
        printf("-1\n");
    }
    
    return 0;
}
