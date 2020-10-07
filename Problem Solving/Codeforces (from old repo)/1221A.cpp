#include <bits/stdc++.h>
using namespace std;
 
void loop (int i , int n)
{
    if (i < n)
    {
        int j , flag = 0 , l , k , m1 , m2 , me , ma ;
        scanf("%d", &j);
        int array [j] ;
        for (l = 0 ; l < j ; l++) scanf("%d", &array[l]);
 
        for (l = 0 ; l < j ; l++)
        {
            for (k = 0 , m1 = 0 , m2 = 0 , me = 0 , ma = 0 ; k < j ; k++)
            {
                if (array[k] == 2048)
                {
                    flag = 1 ;
                    break ;
                }
                else if (array[k] > m1 && array[k] < 2048)
                {
                    m2 = m1 ;
                    ma = me ;
                    m1 = array[k];
                    me = k ;
                }
                else if (array[k] > m2 && array[k] < 2048)
                {
                    m2 = array[k];
                    ma = k ;
                } 
            }
 
            if (m1 + m2 == 2048) flag = 1 ;
            if (flag == 1) break ;
            array[me] = m1 + m2 ;
            array[ma] = -1 ;
        }
 
        (flag == 1) ? printf("YES\n") : printf("NO\n");
 
        loop (i + 1 , n);
 
    }
}
int main ()
{
    int n ;
    scanf("%d", &n);
    loop (0 , n);
    return 0 ;
}
