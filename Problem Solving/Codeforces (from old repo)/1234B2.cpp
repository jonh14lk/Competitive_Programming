#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int 
#define pb push_back 
#define in (int i = 0 ; i < n ; i++)
#define jn (int j = r.size() - 1 ; j >= 0 ; j--)
#define kn (int k = 0 ; k < n ; k++)
#define wq while (q--)
 
queue <lli> f ;
set <lli> s ;
vector <int> r ;
 
int main ()
{
    lli n , k , aux , aux2 ;
    cin >> n >> k ;
 
    for in
    {
        cin >> aux ;
 
        if(s.find(aux) == s.end()) 
        {
            if (f.size() >= k)
            {
                s.erase(f.front()); 
                f.pop();
            }
 
            f.push(aux);
            s.insert(aux);
        }
    }
    
    
    cout << f.size() << endl ;
    
    while (!f.empty())
    {
        r.pb(f.front());
        f.pop();
    }
 
    for jn
    {
        if (j == 0)
        {
            cout << r[j] << endl ;
        }
        else
        {
             cout << r[j] ;
             cout << " "  ;
        }
    }
 
    return 0 ;
}
