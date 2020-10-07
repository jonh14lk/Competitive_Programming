
#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n , aux ;
        cin >> n ;
 
        vector <int> v ;
        vector <pair<int,int>> impares ;
        vector <pair<int,int>> pares ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> aux ;
            v.pb(aux);
        }
 
        bool flag = false ;
 
        for (int i = 0 ; i < n ; i++)
        {
            if (v[i] % 2 != 0)
            {
                impares.pb(make_pair(v[i] , i));
            }
            else if (v[i] % 2 == 0)
            {
                pares.pb(make_pair(v[i] , i));
            }
        }
 
        if (pares.size() > 0)
        {
            cout << pares.size() << endl ;
 
            for (int i = 0 ; i < pares.size() ; i++)
            {
                cout << pares[i].second + 1 << " " ;
            }
 
            cout << endl ;
        }
        else if (impares.size() % 2 == 0 && impares.size() > 0)
        {
            cout << impares.size() << endl ;
 
            for (int i = 0 ; i < impares.size() ; i++)
            {
                cout << impares[i].second  + 1 << " " ;
            }
 
            cout << endl ;
        }
        else if (impares.size() % 2 != 0 && impares.size() > 1)
        {
            cout << impares.size() - 1 << endl ;
 
            for (int i = 0 ; i < impares.size() - 1 ; i++)
            {
                cout << impares[i].second + 1 << " " ;
            }
 
            cout << endl ;
        }
        else
        {
            cout << "-1\n" ;
        }
 
        
    }
 
    return 0 ;
}
