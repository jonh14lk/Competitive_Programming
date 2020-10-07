#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <lli> v;
vector <lli> v2;
 
int main ()
{
    int q ;
    cin >> q ;
    lli a , b , c , aux ;
 
    while (q--)
    {
        cin >> a >> b >> c ;
        v.clear();
        v2.clear();
 
        for (int i = 0 ; i < b ; i++)
        {
            cin >> aux ;
            v.pb(aux);
        }
 
        for (int i = 0 ; i < c ; i++)
        {
            cin >> aux ;
            v2.pb(aux);
        }
 
        sort(v.begin() , v.end());
        sort(v2.begin() , v2.end());
 
        if (v[b - 1] > v2[c - 1])
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
        
    }
    return 0 ;
}
