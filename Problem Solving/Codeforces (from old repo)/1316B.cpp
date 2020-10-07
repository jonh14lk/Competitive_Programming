#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int q , n ;
string s ;
vector <pair<string , int>> v ;
 
string my_rev (int k)
{
    if (k != 1 && k != n)
    {
        int s1 = k - 1 , f1 = n - s1 ;
 
        string s2 = s.substr (s1 , f1);
        string s3 = s.substr(0 , s1);
 
        if (k % 2 == n % 2)
        {
            reverse (s3.begin() , s3.end()) ;
        }
 
        string s4 = s2 + s3 ;
        
        return s4 ;
    }
    else if (k == 1)
    {
        return s ;
    }
    else if (k == n)
    {
        string aux = s ;
        reverse (aux.begin() , aux.end()) ;
        return aux ;
    }
}
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    cin >> q ;
 
    while (q--)
    {
        v.clear();
        cin >> n >> s ;
 
        for (int k = 1 ; k <= n ; k++)
        {
            v.pb(make_pair(my_rev(k) , k)) ;
        }
 
        sort(v.begin() , v.end());
 
        cout << v[0].first << endl << v[0].second << endl ;
    }
 
    return 0 ;
}
