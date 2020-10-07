#include <bits/stdc++.h>
using namespace std;

int compare(char str1[],char str2[])
{
    for(int i = 0 ; str1 [i] != '\0' ; i++ )
    {
         if(str1 [i] > str2 [i]) return 1;
         else if(str1 [i] < str2 [i]) return -1;
    }

    return 0;
}
int main()
{
    char str1 [1000] , str2 [1000] ; 

    while(scanf(" %s %s", str1 , str2) == 2)
    {
        for(int i = 0 ; str1 [i] != '\0' ; i++)
        {
            if(str1 [i] >= 'A' && str1 [i] <= 'Z') str1[i] = str1[i] + 32 ;        
            if(str2 [i] >= 'A' && str2 [i] <= 'Z') str2[i] = str2[i] + 32 ;      
        }

        
        printf("%d\n",compare(str1,str2));
    }
    return 0;
}
