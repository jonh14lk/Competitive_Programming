#include <bits/stdc++.h>
using namespace std;
 
void loop (int i , int num)
{
    if (i < num)
    {
        int c , m , x ;
        scanf("%d%d%d", &c , &m , &x);
        printf("%d\n", min(min(c, m), min(min(c, m), (c + m + x) / 3)));
        loop (i + 1 , num);
    }   
}
int main ()
{
    int num ;
    scanf("%d", &num);
    loop (0 , num);
    return 0 ;
}
