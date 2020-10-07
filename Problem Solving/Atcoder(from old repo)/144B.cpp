#include <bits/stdc++.h>
using namespace std ;
 
int main() 
{
    int a , b , flag = 0 ;
    scanf("%d", &a);
 
    for (int i = 0 ; i <= 9 ; i++)
    {
        for (int j = 0 ; j <= 9 ; j++)
        {
            if (i * j == a)
            {
                flag = 1 ;
            }
        }
    }
 
    (flag == 1) ? printf("Yes\n") : printf("No\n");
 
 
    return 0;
}
