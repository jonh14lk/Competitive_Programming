#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v;
int upperbound (int n , int x) 
{
    int i = 0 ;
    int f = n ;
    int m ;
 
    while (i < f) 
    {
        m = (i + f) / 2 ;
 
        if (x >= v[m]) i = m + 1 ;
        else f = m  ;
 
    }
 
    return i ;
}
int main ()
{
    int n , aux , m ;

    cin >> n ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> aux ;
        v.pb(aux);
    }
 
    sort(v.begin() , v.end());
 
    cin >> m ;
    cout << upperbound(n , m) << endl ;
 
    return 0 ;
}