#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int n ;
    cin >> n ;
    vector <lli> v(n) ;
    vector <lli> ans(n);
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> v[i] ;
    }   
 
    lli maxx = 0 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        if (i == 0)
        {
            ans[i] = v[i] ;
            maxx = v[i];
        }
        else if (v[i] < 0)
        {
            maxx = max(abs(v[i]) , maxx);
            ans[i] = maxx - abs(v[i]);
        }
        else 
        {       
            maxx += v[i] ;
            ans[i] = maxx ;
        }
    }
 
    for (int i = 0 ; i < n ; i++)
    {
        cout << ans[i] << " " ;
    }
 
    cout << endl ;
 
    return 0 ;
 
}
