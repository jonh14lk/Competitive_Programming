#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
 
int main ()
{
    int n , aux , maxp , minp , r = 0 ;
    scanf("%d", &n);
 
    for (int i = 0 ; i < n ; i++)
    {
        vector <int> v ;
 
        for (int i = 0 ; i < 4 ; i++)
        {
            scanf("%d", &aux);
            v.pb(aux);
        }
 
        maxp = v[0] , minp = 1 , r = 0 ;
 
        while(v[1] >= 0)
        {
            if (v[3] == maxp && v[2] == minp) 
            {
                r = abs(v[3] - v[2]) ;  
                break ;
            }
            else if (v[2] == maxp && v[3] == minp)
            {     
                r = abs(v[3] - v[2]) ;     
                break ;
            }
            else if (v[1] == 0)
            {
                r = abs(v[3] - v[2]) ;  
                break ;
            }
 
            if (v[3] > v[2])
            {
                if (v[3] < maxp) 
                {
                    v[3]++;
                    v[1]--;
                }
                else if (v[2] > minp)
                {
                    v[2]--;
                    v[1]--;
                }
                
            }
            else 
            {
                if (v[2] < maxp) 
                {
                    v[2]++;
                    v[1]--;
                }
                else if (v[3] > minp)
                {
                    v[3]--;
                    v[1]--;
                }
            }
            
        }
 
        printf("%d\n", r);        
    }
    return 0 ;
}
