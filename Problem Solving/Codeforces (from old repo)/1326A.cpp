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
 
        if (n == 1 || n == 0)
        {
            cout << "-1\n" ;
        }
        else if ((n - 1) % 3 == 0)
        {
            for (int i = 0 ; i < n - 2 ; i++)
            {
                cout << "5" ;
            }
 
            cout << "33\n" ;
        }
        else
        {
            for (int i = 0 ; i < n - 1 ; i++)
            {
                cout << "5" ;
            }
 
            cout << "3\n" ;
        }
    }
 
    return 0 ;
 
}
