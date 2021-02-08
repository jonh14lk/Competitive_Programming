// Grafo Bipartido 
// 1 - nao possui ciclo de tamanho impar
// 2 - podemos colorir todos os vertices usando apenas duas cores de maneira que uma aresta nunca ligue dois vértices da mesma cor
// 3 - Se quisermos checar se um grafo eh bipartido ou nao, simplesmente checamos se ele pode ser colorido usando duas cores.

#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 10000

int n , m , a , b ;                      
vector <int> adj [MAXN] ;  
int color [MAXN] ;

void colore (int x)
{ 
    color[x] = 0 ; 

    vector <int> f ; 
    f.pb(x) ; 

    int pos = 0 ;

    while (pos < f.size())
    {
        int at = f[pos] ; 
        pos++ ;

        for (int i = 0 ; i < adj[at].size() ; i++)
        {
            int v = adj[at][i] ;

            if (color[v] == -1)
            { 
                color[v] = 1 - color[at] ;             
                f.pb(v) ; 
            }
        }
    }
}
bool is_bipartido ()
{
    for (int i = 0 ; i < n ; i++)
    {
        if (color[i] == -1)
        {       
            colore(i) ;          
        }
    }

    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < adj[i].size() ; j++)
        {
            if (color[i] == color[adj[i][j]]) 
            {
                return false ; 
            }
        }
    }

    return true ;
}
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;

    cin >> n >> m ;

    memset(color , -1 , sizeof(color)) ;

    for (int i = 0 ; i < m ; i++)
    {
        cin >> a >> b ;
        adj[a].pb(b) ;
        adj[b].pb(a) ;
    }

    (is_bipartido()) ? cout << "YES\n" : cout << "NO\n" ;

    return 0 ;
}
