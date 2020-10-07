#include <bits/stdc++.h>
using namespace std ;
 
#define pb push_back
#define lli long long int
 
vector <lli> v ;
int main ()
{
    int q ;
    cin >> q ;
 
    while (q--)
    {
        v.clear() ;
        int n ;
        cin >> n ;
        int t = 2 * n ;
        lli aux ;
        lli s1 = 0 , s2 = 0 ;
 
        for (int i = 0 ; i < t ; i++)
        {
            cin >> aux ;
            v.pb(aux);
        }
 
        sort(v.begin() , v.end()) ;
 
        cout << v[(t / 2)] - v[(t / 2) - 1]  << endl ;
    }
 
    return 0 ;
}
