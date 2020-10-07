#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v;
int main ()
{
    int n , aux ;
    cin >> n ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> aux ;
        v.pb(aux);
    }
 
    sort(v.begin() , v.end());
 
    int q ;
    cin >> q ;
    lli m , r ;
 
    for (int i = 0 ; i < q ; i++)
    {
        cin >> m ;
 
        vector<int>::iterator u = upper_bound(v.begin(), v.end(), m) ;
        cout << (u - v.begin()) << endl ;
    }
 
    return 0 ;
}
