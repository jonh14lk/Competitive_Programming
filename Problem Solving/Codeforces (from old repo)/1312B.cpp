#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n ;
        cin >> n ;
        vector <int> v ;
 
        for (int i = 0 ; i < n ; i++)
        {
            int aux ;
            cin >> aux ;
            v.pb(aux);
        }
 
        sort(v.begin() , v.end());
 
        for (int i = n - 1 ; i >= 0 ; i--)
        {
            cout << v[i] << " " ;
        }
 
        cout << endl ;
    }
 
    return 0 ;
}
