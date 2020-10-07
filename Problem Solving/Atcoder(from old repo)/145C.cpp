#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
 
int main ()
{
    int n ;
    scanf("%d", &n);
 
    vector <int> v ;
    vector <int> v2 ;
 
    int aux1 , aux2 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        scanf("%d%d", &aux1 , &aux2);
        v.pb(aux1);
        v2.pb(aux2);
    }
 
    double c = 0.0 ;
    double r , r2 , r3 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            r = pow((v[i] - v[j]) , 2);
            r2 = pow((v2[i] - v2[j]) , 2);
            r3 = sqrt(r + r2);
            c = c + r3;
        }
    }
 
    printf("%.10lf", c / n);
 
    return 0 ;
}
