#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()  
{
    string a ;
    cin >> a ;
    int n = a.size() -  1 , c = 0;
 
    for (int i = 0 ; i < a.size() / 2  ; i++)
    {
        if (a[n - i] != a[i]) c++ ;
    }
 
    cout << c << endl ;
 
    return 0;  
}  
