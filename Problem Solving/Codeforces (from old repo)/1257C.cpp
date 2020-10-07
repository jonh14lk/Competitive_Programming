#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
 
int main ()
{
    int q ;
    scanf("%d", &q);
 
    for (int i = 0 ; i < q ; i++)
    {
        int counted [900000];
        vector <int> v ;
        int n , aux , r ;
        scanf("%d", &n);
 
        memset(counted , -1 , sizeof(counted));
        v.clear();
        r = INT_MAX ;
 
        for (int k = 0 ; k < n ; k++)
        {
            scanf("%d", &aux);
            v.pb(aux);
        }
 
        for (int k = 0 ; k < n ; k++)
        {
            if (counted[v[k]] == -1)
            {
                counted[v[k]] = k ;
            }
            else
            {
                if ((k - counted[v[k]]) + 1 < r)
                {
                    r = (k - counted[v[k]]) + 1 ;
                }
                counted[v[k]] = k ;
            }
            
        }
 
        (r == INT_MAX) ? printf("-1\n") :printf("%d\n", r);
 
    }
    return 0 ;
}
