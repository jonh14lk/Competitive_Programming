#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v;
int lowerbound (int n , int x) 
{
    int i = 0 ;
    int f = n ;
    int m ;
 
    while (i < f) 
    {
        m = (i + f) / 2 ;
 
        if (x <= v[m]) f = m  ;
        else i = m + 1 ;
 
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
    cout << lowerbound(n , m) << endl ;
 
    return 0 ;
}