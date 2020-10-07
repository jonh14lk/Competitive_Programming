#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
#define pf push_front 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    deque <char> d ;
 
    string s ;
    cin >> s ; 
 
    for (int i = 0 ; i < s.size() ; i++)
    {
        d.pb(s[i]) ;
    }
 
    int q ;
    cin >> q ;
    int rev_count = 0 ;
 
    while (q--)
    {
        int op , pos ;
        char aux;
        cin >> op ;
 
        if (op == 1)
        {
            rev_count++ ;
        }
        else if (op == 2)
        {
            cin >> pos >> aux ;
 
            if (pos == 1 && rev_count % 2 != 0)
            {
                d.pb(aux);
            }
            else if (pos == 1 && rev_count % 2 == 0)
            {
                d.pf(aux);
            }
            else if (pos == 2 && rev_count % 2 != 0)
            {
                d.pf(aux);
            }
            else if (pos == 2 && rev_count % 2 == 0)
            {
                d.pb(aux);
            }
 
        }
    }
 
    if (rev_count % 2 != 0)
    {
        deque <char> :: reverse_iterator rit = d.rbegin() ;
 
        for (rit = d.rbegin() ; rit != d.rend() ; rit++) 
        {
            cout << *rit ; 
        }
 
        cout << endl ;
    }
    else
    {
        deque <char> :: iterator it ; 
 
        for (it = d.begin() ; it != d.end() ; it++) 
        {
            cout << *it ; 
        }
 
        cout << endl ;
    }
    
    return 0 ;
}
