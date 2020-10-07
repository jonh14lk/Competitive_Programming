#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    string s ;
    cin >> s ;
 
    if (s[0] == 'A' && s[1] == 'A' && s[2] == 'A')
    {
        cout << "No\n" ;
    }
    else if (s[0] == 'B' && s[1] == 'B' && s[2] == 'B')
    {
        cout << "No\n" ;
    }
    else 
    {
        cout << "Yes\n" ;
    }
    return 0 ;
}
