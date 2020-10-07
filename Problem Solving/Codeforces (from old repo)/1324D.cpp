#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    lli n ;
    cin >> n ;
 
    vector <lli> v(n);
    vector <lli> v2(n);
    vector <lli> dif(n);
   
    for (int i = 0 ; i < n ; i++)
    {
        cin >> v[i] ;
    }
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> v2[i] ;
        dif[i] = v[i] - v2[i] ;
    }
 
    lli ans = 0 , biggest = INT_MIN ;
    
    sort(dif.begin() , dif.end());
    int j = 0 ;
 
    for (int i = n - 1 ; i >= 0 ; i--)
    {
        while(1) 
        {
            if (j < i && dif[i] + dif[j] <= 0)
            {
                j++ ;
            }
            else
            {
                break ;
            }
        }
 
        ans += max(0 , i - j) ;
    }
 
    cout << ans << endl ;
}
