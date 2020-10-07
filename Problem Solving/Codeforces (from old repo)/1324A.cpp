#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n ;
        cin >> n ;
        vector <int> v (n);
        bool par = false , impar = false ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> v[i] ;
 
            if (v[i] % 2 == 0)
            {
                par = true ;
            }
            else 
            {
                impar = true ;
            }
        }
 
        if (!par && impar)
        {
            cout << "YES\n" ;
        }
        else if (par && !impar)
        {
            cout << "YES\n" ;
        }
        else
        {
            cout << "NO\n" ;
        }
    }
}
