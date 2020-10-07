#include <bits/stdc++.h>
using namespace std;

int main ()
{
    int i , j , l1 , j1 , mov = 0 , matriz[5][5];

    for(i = 0 ; i < 5 ; i++)
    {
        for (j = 0 ; j < 5 ; j++)
        {
            scanf("%d", &matriz[i][j]);
            if (matriz [i][j] == 1) 
            {
                l1 = i ;
                j1 = j ;
            }
        }
    }
    
    int resposta = abs (l1 - 2) + abs(j1 - 2) ; 
    printf("%d\n", resposta);

    return 0 ;
}
