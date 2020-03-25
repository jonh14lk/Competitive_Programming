// lower - primeiro maior ou igual a x
// upper - ultimo menor ou igual a x

#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back

vector <int> v ;
int main()
{
    int n , aux ;
    cin >> n ;

    for (int i = 0 ; i < n ; i++)
    {
        cin >> aux ;
        v.pb(aux);
    }

    sort(v.begin() , v.end());

    int q ;
    cin >> q ;

    while (q--)
    {
        cin >> aux ;
        vector <int> :: iterator low = lower_bound (v.begin() , v.end() , aux) ; 
        vector <int> :: iterator up = upper_bound (v.begin() , v.end() , aux) ;
        
        cout << (low - v.begin()) << " " << (up - v.begin()) - 1 << endl ;
    }

    return 0 ;
}
