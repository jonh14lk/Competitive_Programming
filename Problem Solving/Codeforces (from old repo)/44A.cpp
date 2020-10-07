#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jn (int j = 0 ; j < n ; j++)
#define kn (int k = 0 ; k < n ; k++)
#define wq while (q--)
 
set < pair <string , string> > s ;
 
int main ()
{
    int n ;
    cin >> n ;
 
    string a ;
    string b ;
 
    for in
    {
        cin >> a >> b ;
        s.insert(make_pair(a,b));
    }
 
    cout << s.size() << endl ;
    
    return 0 ;
}
