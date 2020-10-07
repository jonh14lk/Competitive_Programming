#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    int tam , i;
    scanf("%d", &tam);
    char string [100000];
    scanf(" %s", string);
    int array [5] , printed = 0 ;
 
    for (i = 0 ; i < 5 ; i++) array[i] = 0 ;
 
    for (i = 0 ; i < tam ; i++)
    {
        if (string[i] == 'z') array[0]++ ;
        if (string[i] == 'e') array[1]++ ;
        if (string[i] == 'r') array[2]++ ;
        if (string[i] == 'o') array[3]++ ;
        if (string[i] == 'n') array[4]++ ;
    }
 
    for (i = 0 ; i < tam ; i++)
    {
        if (array[3] > 0 && array[4] > 0 && array[1] > 0)
        {
            (printed == 0) ? printf("1") : printf(" 1") ;
            printed++ ;
            array[3]-- ;
            array[4]-- ;
            array[1]-- ;
        }
        else if (array[0] > 0 && array[1] > 0 && array[2] > 0 && array[3] > 0)
        {
            (printed == 0) ? printf("0") : printf(" 0") ;
            printed++ ;
            array[0]-- ;
            array[1]-- ;
            array[2]-- ;
            array[3]-- ;
        }
        else break ;
    }
 
    printf("\n");
    return 0 ;
}
