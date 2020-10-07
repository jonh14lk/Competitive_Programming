#include <bits/stdc++.h>
using namespace std;

int verify (int num)
{
    if(num > 0) return (num % 10 == 4 || num % 10 == 7) ? verify(num / 10) : 0 ;
    else return 1 ;
}
int main ()
{
    int num , i , div = 0;
    scanf("%d", &num);

    for (i = 1 ; i <= num ; i++)
    {
        if (verify(i) == 1)
            if(num % i == 0) div = 1 ;
    }

    (div == 0) ? printf("NO\n") : printf("YES\n") ;
    return 0 ;
}
