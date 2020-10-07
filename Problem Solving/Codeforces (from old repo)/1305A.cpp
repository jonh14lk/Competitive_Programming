#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n , a ;
        cin >> n ;
 
        vector <int> v ;
        vector <int> v2 ;
        
        for (int i = 0 ; i < n ; i++)
        {
            cin >> a ;
            v.pb(a);
        }
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> a ;
            v2.pb(a);
        }
 
        sort(v.begin() , v.end());
        sort(v2.begin() , v2.end());
 
        for (int i = 0 ; i < n ; i++)
        {
            cout << v[i] << " " ;
        }
        cout << endl ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cout << v2[i] << " " ;
        }
 
        cout << endl ;
    }
 
    return 0 ;
}
