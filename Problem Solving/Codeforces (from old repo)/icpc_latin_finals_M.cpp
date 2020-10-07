#include <bits/stdc++.h>
using namespace std ;
 
#define pb push_back
 
int main ()
{
    int n , m , aux ;
    scanf("%d%d", &n , &m);
    vector <int> v ;
 
    for (int i = 0 ; i < n ; i++)
    {
        scanf("%d", &aux);
        v.pb(aux);
    }
 
    int at = 0  , maior = -1 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        at = 0 ;
 
        for (int j = i; j < n ; j++)
        {
            at++ ;
            if (v[j] + m < v[j + 1]) 
            {
                break ;
            }
        }
 
        if (at > maior) maior = at ;
    }
 
    printf("%d\n", maior);
    return 0 ;
}
