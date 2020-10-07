#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v ;
int main ()
{
    int a , b , c ;
    cin >> a >> b >> c ;
    v.pb(a) , v.pb(b) , v.pb(c) ;
 
    sort(v.begin() , v.end());
 
    if (v[0] == v[1] && v[1] != v[2])
    {
        cout << "Yes\n" ;
    }
    else if (v[0] != v[1] && v[1] == v[2])
    {
        cout << "Yes\n" ;
    }
    else
    {
        cout << "No\n" ;
    }
    
    return 0 ;
}
