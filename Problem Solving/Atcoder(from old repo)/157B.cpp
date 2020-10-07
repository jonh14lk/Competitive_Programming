#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define lli long long int
int bingo [3][3];
 
void mark (int aux)
{
    for (int i = 0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
        {
            if (bingo[i][j] == aux)
            {
                bingo[i][j] = INT_MIN ;
                return ;
            }
        }
    }
}
bool verify ()
{
    if (bingo[0][0] == INT_MIN && bingo[0][1] == INT_MIN  && bingo[0][2] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[1][0] == INT_MIN && bingo[1][1] == INT_MIN  && bingo[1][2] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[2][0] == INT_MIN && bingo[2][1] == INT_MIN  && bingo[2][2] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[0][0] == INT_MIN && bingo[1][0] == INT_MIN  && bingo[2][0] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[0][1] == INT_MIN && bingo[1][1] == INT_MIN  && bingo[2][1] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[0][2] == INT_MIN && bingo[1][2] == INT_MIN  && bingo[2][2] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[0][0] == INT_MIN && bingo[1][1] == INT_MIN  && bingo[2][2] == INT_MIN )
    {
        return true ;
    }
    else if (bingo[0][2] == INT_MIN && bingo[1][1] == INT_MIN  && bingo[2][0] == INT_MIN )
    {
        return true ;
    }
    else 
    {
        return false ;
    }
}
int main()
{   
    for (int i = 0 ; i < 3 ; i++)
    {
        for (int j = 0 ; j < 3 ; j++)
        {
            cin >> bingo [i][j] ;
        }
    }
 
    int q , aux ;
    cin >> q ;
    
    while (q--)
    {
        cin >> aux ;
        mark (aux);
    }
 
    if (verify())
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
 
    return 0;
}
