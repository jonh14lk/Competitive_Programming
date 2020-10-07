#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jm (int j = 0 ; j < m ; j++)
 
int main ()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    
    char str [256];
    scanf(" %s", str);
 
    if (strcmp(str , "SAT") == 0)
    {
        printf("1\n");
        return 0 ;
    }
    else if (strcmp(str , "MON") == 0)
    {
        printf("6\n");
        return 0 ;
    }
    else if (strcmp(str , "TUE") == 0)
    {
        printf("5\n");
        return 0 ;
    }
    else if (strcmp(str , "WED") == 0)
    {
        printf("4\n");
        return 0 ;
    }
    else if (strcmp(str , "THU") == 0)
    {
        printf("3\n");
        return 0 ;
    }
    else if (strcmp(str , "FRI") == 0)
    {
        printf("2\n");
        return 0 ;
    }
    else if (strcmp(str , "SUN") == 0)
    {
        printf("7\n");
        return 0 ;
    }
 
    return 0 ;
}
