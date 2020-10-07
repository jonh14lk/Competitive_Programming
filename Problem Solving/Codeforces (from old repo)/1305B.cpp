#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 200001
 
vector <int> v ;
int visited [MAXN];
int main ()
{
    string s ;
    cin >> s ;
    int ans = 0 , last = INT_MAX ;
    bool flag = true ;
 
    for (int i = 0 ; i < s.size() ; i++)
    {
        if (s[i] == '(' && !visited[i])
        {
            last = INT_MAX ;
 
            for (int j = i + 1 ; j < s.size() ; j++)
            {
                if (s[j] == ')' && !visited[j])
                {
                    last = j ;
                }
            }
 
            if (last == INT_MAX)
            {
                flag = false ;
                break ;
            }
            else
            {
                ans += 2 ;
                v.pb(i + 1);
                v.pb(last + 1);
                visited[i] = 1 ;
                visited[last] = 1 ;
            }
            
        }
    }
 
    if (ans != 0)
    {
        cout << "1" << endl ;
        cout << ans << endl ;  
        sort(v.begin() , v.end());
 
        for (int i = 0 ; i < v.size() ; i++)
        {
            cout << v[i] << " ";
        } 
 
        cout << endl ;
    }
    else
    {
        cout << "0\n" ;
    }
    
 
    return 0 ;
}
