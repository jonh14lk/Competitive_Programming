#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 1000

int n , m ;
int parent [MAXN] ;
vector <int> adj_list [MAXN] ;

int find (int i)
{ 
    if (parent[i] == -1) 
    {
        return i ; 
    }
    else 
    {
        return find (parent[i]) ; 
    }
} 
void join (int x , int y)
{ 
    int x_father = find (x) ; 
    int y_father = find (y) ; 
 
    if (x_father != y_father)
    { 
       parent[x_father] = y_father ; 
    } 
}  
bool is_cycle () 
{ 
    for (int i = 0 ; i < n ; i++) 
    { 
        for (int j = 0 ; j < adj_list[i].size() ; j++)
        {
            int x = find (i) ; 
            int y = find (adj_list[i][j]) ; 
    
            if (x == y) 
            {
                return true ; 
            }

            join (x , y) ;
        } 
    } 

    return false ; 
} 
void initialize ()
{
    for (int i = 0 ; i < MAXN ; i++) 
    {
        adj_list[i].clear();
    }
}
int main ()
{
    int a , b , j = 1 ;
    
    while (scanf("%d%d", &n , &m) != EOF) 
    {
        initialize ();
        memset (parent , -1 , sizeof(parent)) ; 
    
        for (int i = 0 ; i < m ; i++) 
        {
            cin >> a >> b ;
            adj_list[a].push_back(b) ;
        }
    
        if (is_cycle()) 
        {
            cout << j << " 1" << endl ;
        }
        else 
        {
            cout << j << " 0" << endl ;
        }
        
        j++ ;
    }

    return 0 ;
}
