#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    int q ;
    cin >> q ;
    while (q--)
    {
        lli n , d ;
        cin >> n >> d ;
        
        if (n >= d)
        {
            cout << "YES" << endl ;
        }
        else 
        {
            lli x = 1 ;
            int flag = 0 ;
            double ans = INT_MAX , ans_ant = INT_MAX ;
            
            while (1)
            {
                ans_ant = ans ;
                ans = x + ceil((double) d / (double)(x + 1)) ;
                
                if (ans <= n)
                {
                    cout << "YES" << endl ;
                    flag = 1 ;
                    break ;
                }
 
                if (ans_ant < ans)
                {
                    break ;
                }
 
                x++ ;
            }
            
            if (flag == 0)
            {
                cout << "NO" << endl ;
            }
            
        }
    }
    return 0;
}
