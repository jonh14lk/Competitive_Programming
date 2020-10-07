#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int n , ans = 0 ;
    string s ;
    cin >> n >> s ;
 
    for (int i = 25 ; i >= 0 ; i--)
    {
        for(int j = 0 ; j < s.size() ; j++)
        {
            if (s[j] == 'a' + i && j > 0 && s[j - 1] == i + 'a' - 1)
            {
                s.erase(s.begin() + j) ;
                ans++ ;
                j = -1 ;
            }
            else if  (s[j] == 'a' + i && j < s.size() - 1 && s[j + 1] == i + 'a' - 1)
            {
                s.erase(s.begin() + j) ;
                ans++ ;
                j = -1 ;
            }
        }
    }
 
    cout << ans << endl ;
 
    return 0 ;
}
