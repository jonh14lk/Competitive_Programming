#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jn (int j = 0 ; j < n ; j++)
#define kn (int k = 0 ; k < n ; k++)
#define wq while (q--)
 
map <string , int> m ;
 
int main ()
{
    int n ;
    cin >> n ;
 
    string a ;
 
    for in
    {
        cin >> a ;
 
        if (m[a] == 0)
        {
            cout << "OK" << endl ;
 
            m[a]++ ;
        }
        else
        {
            cout << a ;
            cout << m[a] << endl ;
 
            m[a]++;
        }
    }
    
    return 0 ;
}
