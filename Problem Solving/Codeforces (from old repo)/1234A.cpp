#include <bits/stdc++.h>
using namespace std ;
 
void loop (int l , int i)
{
    if (l < i)
    {
        int n , sum = 0 , k = 1 ;
        scanf("%d", &n);
        int array [n];
 
        for (int j = 0 ; j < n ; j++)
        {
            scanf("%d", &array[j]);
            sum = sum + array[j];
        }
 
        while (k * n < sum)
        {
            if (k * n >= sum) break ;
 
            k++ ;
        }
        
        printf("%d\n", k);
        loop (l + 1 , i);
    }
}
int main() 
{
    int i ;
    scanf("%d", &i);
 
    loop (0 , i);
    return 0;
}
