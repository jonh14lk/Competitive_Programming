#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
int main ()
{
    int q ;
    scanf("%d", &q);
 
    while(q--)
    {
        int n ;
        scanf("%d", &n);
 
        vector <int> v ;
        vector <int> v2;
 
        int aux ;
 
        for (int i = 0 ; i < n ; i++)
        {
            scanf("%d", &aux);
            v.pb(aux);
        }
 
        for (int i = 0 ; i < n ; i++)
        {
            scanf("%d", &aux);
            v2.pb(aux);
        }
 
        bool flag = true  ;
        int dif = INT_MAX ;
        int seg = INT_MAX ;
 
        for (int i = 0 ; i < n ; i++)
        {
            if (v[i] > v2[i])
            {
                flag = false ;
                break ;
            }
            if (v[i] != v2[i])
            {
                if (dif == INT_MAX)
                {
                    dif = v[i] - v2[i];
                    seg = i ;
                }
                else if (i == seg + 1)
                {
                    if (v[i] - v2[i] != dif)
                    {
                        flag = false ;
                        break;
                    }
                    else
                    {
                        seg = i ;
                    }
                }
                else
                {
                    flag = false ;
                    break ;
                }
            }
        }
 
        (flag) ? printf("YES\n") : printf("NO\n");
    }
    return 0 ;
}
