#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define lli long long int
 
int main()
{   
    int n , m ;
    cin >> n >> m ;
 
    if (n == 1 && m == 0)
    {
        cout << "0\n";
        return 0 ;
    }
    
    int array [n];
 
    for (int i = 0 ; i < n ; i++)
    {
        array[i] = 0 ;
    }
    
    array[0] = 1 ;
 
    for (int i = 0 ; i < m ; i++)
    {
        int p , k ;
        cin >> p >> k ;
        
        if (array[p - 1] == 0)
        {
            array[p - 1] = k ;
        }
        else if (p - 1 == 0)
        {
            if (array[0] == 1)
            {
                array[0] = k ;
            }
            else if (array[0] == k)
            {
                array[0] = k ;
            }
            else 
            {
                cout << "-1\n" ;
                return 0 ;
            }
            
        }
        else if (array[p - 1] == k)
        {
            array[p - 1] = k ;
        }
        else
        {
            cout << "-1\n" ;
            return 0 ;
        }
    }
    
    if (array[0] == 0 && n > 1)
    {
        cout << "-1\n" ;
    }
    else
    {
        for (int i = 0 ; i < n ; i++)
        {
            cout << array[i];
        }
 
        cout << endl ;
    }
    
    return 0;
}
