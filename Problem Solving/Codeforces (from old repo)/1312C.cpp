#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 200
 
vector <lli> v ;
set <lli> s ;
int visited [MAXN];
lli pot [MAXN];
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
       v.clear();
       s.clear();
       memset (visited , 0 , sizeof(visited));
 
       lli n , k ;
       cin >> n >> k ;   
 
        for (int i = 0 ; i < n ; i++)
        {
            lli aux ;
            cin >> aux ;
            v.pb(aux);
        }
 
        int size = 0 ;
 
        while (1)
        {
            pot[size] = pow (k , size) ;
            
            if (pot[size] <= pot[size - 1] && size > 0)
            {
                pot[size] = 0 ;
                size-- ;
                break ;
            }
 
            size++ ;
        }
        
        bool can = true ;
 
        for (int i = 0 ; i < n ; i++)
        {
            if (v[i] == 0)
            {
                continue ;
            }
            else if (v[i] == 1 && s.find(v[i]) == s.end() && visited[0] == 0)
            {
                s.insert(v[i]);
                visited[0] = 1 ;
            }
            else if (s.find(v[i]) != s.end())
            {
                can = false ;
                break ;
            }
            else 
            {
                bool flag = false ;
                lli exp , f = size , b = 0 ;
             
                while (b < f) 
                {
                    exp = (b + f) / 2 ;
             
                    if (v[i] >= pot[exp]) 
                    {
                        b = exp + 1 ;
                    }
                    else 
                    {
                        f = exp  ;
                    }
             
                }
 
                b-- ;
                lli sum = 0 ;
                
                for (int j = b ; j >= 0 ; j--)
                {
                    if (visited[j] == 0)
                    {
                        sum += pot[j] ;
                        visited[j] = 1 ;
                    }
                    if (sum == v[i])
                    {
                        s.insert(v[i]) ;
                        flag = true ;
                        break ;
                    }
                    else if (sum > v[i])
                    {
                        sum -= pot[j] ;
                        visited[j] = 0 ;
                    }   
                }
 
                if (!flag)
                {
                    can = false ;
                    break ;
                }
            }
        }
 
        (can) ? cout << "YES\n" : cout << "NO\n" ;
    }
 
    return 0 ;
}
