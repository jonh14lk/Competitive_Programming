#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 500001
 
set <int> s [26] ;
int main()
{
    int n ;
    cin >> n ;
 
    string st ;
    cin >> st ;
 
    for (int i = 0 ; i < st.size() ; i++)
    {
        s[st[i] - 'a'].insert(i) ;
    }
    
    int q ;
    cin >> q ;
 
    while(q--)
    {
        int type ;
        cin >> type ;
 
        if (type == 1)
        {
            int k ;
            char c ;
 
            cin >> k >> c ;
            k-- ;
 
            s[st[k] - 'a'].erase(k) ;
            s[c - 'a'].insert(k) ;
            st[k] = c ;
        }
        else if (type == 2)
        {
            int l , r ;
            cin >> l >> r ;
 
            l-- ;
            r-- ;
 
            int ans = 0 ;
 
            for (int i = 0 ; i < 26 ; i++)
            {
                auto it = s[i].lower_bound(l) ;
 
                if (it != s[i].end() && *it <= r)
                {
                    ans++ ;
                } 
            }
 
            cout << ans << endl ;
        }
    }
    return 0;
}
