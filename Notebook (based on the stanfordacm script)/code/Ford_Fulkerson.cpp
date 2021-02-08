// ford-fulkerson: obter qual o fluxo maximo de um vertice s ate um vertice d 
// 1 - rodar um bfs para descobrir um novo caminho de s ate d 
// 2 - apos isso pego a aresta de menor custo desse caminho e subtraio o valor dela nas outras arestas do caminho 
// 3 - fluxo_maximo += custo da aresta de menor custo desse caminho 
// 4 - rodar isso ate nao existirem mais caminhos disponiveis (com fluxo diferente de 0) entre s e d 
// 5 - o fluxo maximo de s ate d sera a soma das arestas de menor custo de cada caminho feito 

#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 10000
#define INF 999999

int n , m , a , b , c , s , d , max_flow , flow ; 
vector <int> parent ;
vector <int> adj [MAXN] ;
int cost [MAXN][MAXN] ;
bool visited [MAXN] ;

void get_menor_custo (int v , int mincost) 
{   
    if (v == s) 
    {
        flow = mincost ; 
        return ;
    }     
    else if (parent[v] != -1)
    {         
        get_menor_custo(parent[v] , min(mincost , cost[parent[v]][v])) ;         
        cost[parent[v]][v] -= flow ;         
        cost[v][parent[v]] += flow ;     
    } 
} 
void bfs ()
{
    visited[s] = true ;  

    queue <int> q ; 
    q.push(s) ;         
    parent.assign(MAXN , -1) ; 

    while (!q.empty()) 
    {             
        int u = q.front() ; 
        q.pop() ;  

        if (u == d) 
        {
            break ; 
        }

        for (int j = 0 ; j < adj[u].size() ; j++)
        {        
            int v = adj[u][j] ;  

            if (cost[u][v] > 0 && !visited[v])
            {                     
                visited[v] = true ;
                q.push(v) ;
                parent[v] = u ;                 
            }             
        }         
    }         
}
int ford_fulkerson ()
{     
    max_flow = 0 ;   

    while (1)
    {         
        flow = 0 ;     
        memset(visited , false , sizeof(visited));

        bfs() ;
        get_menor_custo(d , INF) ; 

        if (flow == 0)
        {
            break ;
        }      

        max_flow += flow ;     
    }     
    
    return max_flow ; 
}  
int main ()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;

    cin >> n >> m ;

    for (int i = 0 ; i < m ; i++)
    {   
        cin >> a >> b >> c ;
        adj[a].pb(b);
        adj[b].pb(a);
        cost[a][b] = c ;
    }

    cin >> s >> d ;

    cout << ford_fulkerson() << endl ;

    return 0 ;
}
