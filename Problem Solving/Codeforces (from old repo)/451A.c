#include <stdio.h>
 
int verify (int n , int m , int matriz [][m])
{
    int i , j , status = 1 ;
 
    for (i = 0 ; i < n ; i++)
        for (j = 0 ; j < m ; j++) if (matriz[i][j] == 0) status = 0 ;
    
    return (status == 1) ? 1 : 0 ;
}
void game (int n , int m , int i , int matriz [][m] , int *flag)
{
    if (verify(n , m , matriz) == 0)
    {
        if (*flag == 0 ) *flag = 1 ;
        else if (*flag == 1 ) *flag = 0 ;
 
        int l ;
 
        for (l = 0 ; l < n ; l++) matriz[l][i] = -1 ;
 
        for (l = 0 ; l < m ; l++) matriz[i][l] = -1 ;
 
        game (n , m , i + 1 , matriz , flag);
 
    }
    else return ;
}
int main ()
{
    int n , m , i , j ;
    scanf("%d%d", &n , &m);
    int matriz [n][m];
 
    for (i = 0 ; i < n ; i++)
        for (j = 0 ; j < m ; j++) matriz[i][j] = 0 ;
    
    int flag = 1 ;
    game (n , m , 0 , matriz , &flag);
 
    (flag == 0) ? printf("Akshat\n") : printf("Malvika\n");
 
    return 0 ;
}
