#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v;
int binarysearch (int n , int x)
{
    int i = 0 ;
    int f = n - 1 ;
    int m ;
 
    while(i <= f)
    { 
        m = (i + f) / 2 ; 
 
        if(v[m] == x) return m + 1 ; 
        if(v[m] < x)  i = m + 1 ;
        if(v[m] > x)  f = m - 1 ; 
    }
 
    return 0 ; 
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
    cout << binarysearch(n , m) << endl ;
 
    return 0 ;
}