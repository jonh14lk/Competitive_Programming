#include <bits/stdc++.h>
 
using namespace std;
 
int main() 
{
    int num , i , j;
    scanf("%d", &num);
    char matriz [num][num];
    
    for (i = 0 ; i < num ; i++)
    {
        for (j = 0 ; j < num ; j++)
        {
            matriz[i][j] = 'B';
        }
    }
 
    for (i = 0 ; i < num ; i++)
    {
        for (j = 0 ; j < num ; j++)
        {
            if (i % 2 == j % 2) matriz[i][j] = 'W';
        }
    }
 
    for (i = 0 ; i < num ; i++)
    {
        for (j = 0 ; j < num ; j++)
        {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }
 
    return 0;
}
