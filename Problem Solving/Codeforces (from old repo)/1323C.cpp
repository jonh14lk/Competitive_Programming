#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back 
 
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int n ;
    cin >> n ;
    string s ;
    cin >> s ;
 
    int ans = 0 , bal = 0 , flag = 0 , abre_quant = 0 , fecha_quant = 0 ;
 
    for (int i = 0 ; i < s.size() ; i++)
    {
        if (s[i] == '(')
        {
           bal++ ;
           abre_quant++ ;
           if (bal > 0)
           {
                flag = 0 ;
           }
        }
        else if (s[i] == ')')
        {
            bal-- ;
            fecha_quant++;
            if (bal < 0)
            {
                flag = 1 ;
            }
        }
 
        if (flag == 1)
        {
            ans++ ;
        }
    }
 
    if (s.size() % 2 != 0 || abre_quant != fecha_quant)
    {
        cout << "-1\n" ;
    }
    else
    {
        cout << ans << endl ;
    }
}
