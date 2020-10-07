#include <bits/stdc++.h>
using namespace std;
 
int main ()
{
    int tam , i , num , x , soma = 0 , j = 0 , k = 0 ;
    scanf("%d", &tam);
 
    vector <int> v;
 
    for (i = 0 ; i < tam ; i++)
    {
        scanf("%d", &x);
        v.push_back(x);
        soma = soma + x;
    }
 
    soma = soma / 2 ;
    sort(v.begin(), v.end());
 
    for (i = tam - 1 ; i >= 0 ; i--)
    {
        k = k + v[i];
        j++ ;
        if (k > soma) break ;
    }
    
    printf("%d\n", j);
    
    return 0 ;
}
