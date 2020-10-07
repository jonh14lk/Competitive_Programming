#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main ()
{
    int n ;
    cin >> n ;
    int array [n];
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> array[i];
    }
 
    int num_at = 1 , removed = 0;
 
    for (int i = 0 ; i < n ; i++)
    {
        if (array[i] == num_at)
        {
            num_at++;
        }
        else
        {
            removed++;
        }
        
    }
 
    if (num_at == 1)
    {
        cout << "-1" << endl ;
    }
    else
    {
        cout << removed << endl ;
    }
    
 
    return 0 ;
}
