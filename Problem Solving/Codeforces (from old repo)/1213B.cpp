#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define inn (int i = n - 1 ; i >= 0 ; i--)
#define kn (int k = i + 1 ; k < n ; k++)
#define ln (int l = 0 ; l < n - 2 ; l++)
#define pn (int p = 0 ; p <= 100 ; p++)
#define wq while (q--)
 
set <int> s ;
vector <int> v ;
 
int main ()
{
    int q , n , a , p , aux  ;
    cin >> q ;
 
    wq
    {
        s.clear();
        v.clear();
        cin >> n ;
        p = 0 ;
         
        for in
        {
            cin >> a ;
            v.pb(a);
        }
 
        for inn
        {
            if (!s.empty())
            {
                aux = *s.begin(); 
                
                if (v[i] > aux)
                {
                    p++ ;
                }
            }
 
            s.insert(v[i]) ;
        }
 
        cout << p << endl ;
 
    }
 
    return 0 ;
}
