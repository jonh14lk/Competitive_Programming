#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define kn (int k = 0 ; k < n - 1 ; k++)
#define ln (int l = 0 ; l < n - 2 ; l++)
#define pn (int p = 0 ; p <= 100 ; p++)
#define wq while (q--)
 
vector <lli> v;
vector <lli> v2 ;
vector <lli> v3 ;
 
int main ()
{
    lli n , a , aux  , rem ;
    cin >> n ;
 
    for in
    {
        cin >> a ;
        v.pb(a);
    }
 
    for kn
    {
        cin >> a ;
        v2.pb(a);
    }
 
    sort (v.begin(), v.end());   
    sort (v2.begin(), v2.end());  
 
    for in
    {
        if (v[i] != v2[i])
        {
            cout << v[i] << endl ;
            break ;
        }
    }
 
    for ln
    {
        cin >> a ;
        v3.pb(a);
    }
 
    sort (v3.begin(), v3.end()); 
 
    for kn
    {
        if (v2[k] != v3[k])
        {
            cout << v2[k] << endl ;
            break ;
        }   
    }
 
    return 0 ;
}
