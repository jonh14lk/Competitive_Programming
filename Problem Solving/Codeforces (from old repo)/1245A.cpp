#include <bits/stdc++.h>
using namespace std ;
 
int main() 
{
    int n , n1 , n2 , m;
    scanf("%d", &n);
 
    for (int i = 0 ; i < n ; i++)
    {
        scanf("%d%d", &n1 , &n2);
 
        int resto = n1 % n2 ;
 
        while(resto != 0)
        {
            n1 = n2 ;
            n2 = resto ;
            resto = n1 % n2;         
        }
 
        if (n2 == 1) printf("Finite\n");
        else printf("Infinite\n");
    }
    return 0;
}
