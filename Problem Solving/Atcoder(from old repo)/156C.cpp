#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define lli long long int
 
vector <int> v ;
int main ()
{   
    ios_base::sync_with_stdio(false) ;
    cin.tie(NULL) ;
 
    int n , aux ;
    cin >> n ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> aux ;
        v.pb(aux) ;
    }  
 
    lli ans = LLONG_MAX ;
 
    for (int i = 1 ; i <= 100000 ; i++)
    {
        lli at = 0 ;
 
        for (int j = 0 ; j < n ; j++)
        {
            at += pow((v[j] - i) , 2) ;
        }
        
        if (at < ans)
        {
            ans = at ;
        }
    } 
 
    cout << ans << endl ;
    
    return 0;
}
