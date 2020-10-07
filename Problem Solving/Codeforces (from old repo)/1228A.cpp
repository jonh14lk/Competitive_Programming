#include <bits/stdc++.h>
using namespace std ;
 
int condition (int i , int array [])
{
    if (i == 0)
    {
        return 1 ;
    }
 
    int aux = i % 10 ;
    i = i / 10 ;
 
    if (array[aux] == 0)
    {
        array[aux] = array[aux] + 1 ;
        return condition (i , array);
    }
 
    return 0 ;
    
}
int main() 
{
    int a , b , array [10];
    scanf("%d%d", &a , &b);
 
    for (int i = a ; i <= b ; i++)
    {
        for (int i = 0 ; i < 10 ; i++) array[i] = 0 ;
 
        if (condition(i , array) == 1) 
        {
            printf("%d\n", i);
            return 0 ;
        }
    }
 
    printf("-1\n");
 
    return 0;
}
