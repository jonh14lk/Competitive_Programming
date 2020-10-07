#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    char string [256];
    scanf(" %s", string);
    int i , find = 0 ;

    for (i = 0 ; i < strlen(string) ; i++)
    {
        if (find == 0)
            if(tolower(string[i]) == 'h') find++ ;
        if (find == 1)
            if(tolower(string[i]) == 'e') find++ ;
        if (find == 2)
            if(tolower(string[i]) == 'l') 
            {
                find++ ;
                i++;
            }
        if (find == 3)
            if(tolower(string[i]) == 'l') find++ ;
        if (find == 4)
            if(tolower(string[i]) == 'o') find++ ;
    }

    (find == 5) ? printf("YES\n") : printf("NO\n");
    return 0 ;
}
