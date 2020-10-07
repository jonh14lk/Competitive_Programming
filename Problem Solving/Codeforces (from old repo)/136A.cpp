#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int tam ;
    scanf("%d", &tam);
    int array [tam] , array2 [tam] , i ;

    for (i = 0 ; i < tam ; i++) scanf("%d", &array[i]);
    for (i = 0 ; i < tam ; i++) array2[array[i] - 1] = i + 1 ;

    printf("%d", array2[0]);
    for (i = 1 ; i < tam ; i++) printf(" %d", array2[i]);
    printf("\n");

    return 0 ;
}
