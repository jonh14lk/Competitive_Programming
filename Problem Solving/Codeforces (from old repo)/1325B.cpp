#include <bits/stdc++.h>
using namespace std;
 
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
        int n ;
        cin >> n ;
        set <int> s ;
 
        for (int i = 0 ; i < n ; i++)
        {
            lli aux ;
            cin >> aux ;
            s.insert(aux) ;
        }
 
        cout << s.size() << endl ;
 
 
    }
    
    return 0;
}
