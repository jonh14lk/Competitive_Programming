#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    int n ;
    scanf("%d", &n);
 
    if (n % 2 != 0)
    {
        printf("No\n");
        return 0 ;
    }
 
    char string [256];
    scanf(" %s", string);
 
    int t = strlen(string) / 2 ;
    int flag = 0 ;
 
    for (int i = 0 ; i < t ; i++)
    {
        if (string[i] != string[t + i])
        {
            flag = 1 ;
            break ;
        }
    }
 
    (flag) ? printf("No\n") : printf("Yes\n") ;
    return 0 ;
}
