#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int a , b ;
    cin >> a >> b ;
 
    vector <int> v ;
    v.pb(a);
    v.pb(b);
 
    sort(v.begin(), v.end());
 
    if (v[0] == 1 && v[1] == 2) cout << "3\n";
    else if (v[0] == 1 && v[1] == 3) cout << "2\n";
    if (v[0] == 2 && v[1] == 3) cout << "1\n";
 
    return 0 ;
}
