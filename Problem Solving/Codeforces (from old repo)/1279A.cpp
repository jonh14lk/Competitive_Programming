#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int q ;
    cin >> q ;
    lli a , b , c ;
 
    while (q--)
    {
        vector <lli> v;
        cin >> a >> b >> c ;
 
        v.pb(a);
        v.pb(b);
        v.pb(c);
 
        sort(v.begin() , v.end());
 
        if (v[2] > v[1] + v[0] + 1)
        {
            cout << "No\n";
        }
        else
        {
            cout << "Yes\n";
        }
        
 
    }
 
    return 0 ;
}
