#include <bits/stdc++.h>
using namespace std ;
 
void print_array (int i , int n , double array [])
{
    if (i < n)
    {
        if (array[i] == -0)
        {
            printf("0\n");
        }
        else
        {
            printf("%.0lf\n", array[i]);
        }
        
        print_array(i + 1 , n , array);
    }
}
void f2 (int i , int n , double array [] , int op [], int sum)
{
    if (i < n)
    {
        if (op[i] == 1)
        {
            array[i] = array[i] + 1 ;
            sum = sum + 1 ;
 
            if (sum == 0)
            {
                return ;
            }
        }
 
        f2 (i + 1 , n , array , op, sum);
    }
}
void f1 (int i , int n , double array [] , int op [], int sum)
{
    if (i < n)
    {
        if (op[i] == 2)
        {
            array[i] = array[i] - 1 ;
            sum = sum - 1 ;
 
            if (sum == 0)
            {
                return ;
            }
        }
 
        f1 (i + 1 , n , array , op, sum);
    }
}
int main() 
{
    int n, aux = 0 , sum = 0 ;
    scanf("%d", &n);
 
    double array [n];
    int op [n];
 
    memset(op , 0 , sizeof(op));
 
    for (int i = 0 ; i < n ; i++)
    {
        scanf("%lf", &array[i]);
        
        if(aux)
        {
            if((int)array[i] % 2 != 0)
            {
                aux = !aux;
                op[i] = 1 ;
            }
 
            array[i] = floor(array[i] / 2) ;
        }
        else
        {
            if((int)array[i] % 2 != 0)
            {
                aux = !aux;
                op[i] = 2 ;
            }
            
            array[i] = ceil(array[i] / 2) ;
        }
 
        sum = sum + array[i];
    }
 
    if (sum > 0)
    {
        f1(0 , n , array , op , sum);
    }
    else if (sum < 0)
    {
        f2(0 , n , array , op , sum);
    }
    
    print_array(0 , n , array);
 
    return 0;
}
