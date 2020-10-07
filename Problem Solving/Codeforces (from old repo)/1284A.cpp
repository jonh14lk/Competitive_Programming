#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <string> v ;
vector <string> v2 ;
 
int main() 
{
    lli n , m , q , t;
 
    cin >> n >> m ;
 
    string a ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> a ;
        v.pb(a);
    }
 
    for (int i = 0 ; i < m ; i++)
    {
        cin >> a ;
        v2.pb(a);
    }
 
    cin >> q ;
 
    for (int i = 0 ; i < q ; i++)
    {
        cin >> t ;
        cout << v[(t - 1) % n] + v2[(t - 1) % m] << endl ;
    }
 
    return 0;
}
