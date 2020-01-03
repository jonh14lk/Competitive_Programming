#include <bits/stdc++.h>
using namespace std;

#define MAXN 500000
typedef pair <int , int> pii ;  

int n , m ;
int dist [MAXN] ;
bool visited [MAXN] ;
vector <pii> adj_list [MAXN] ;

void dijkstra (int s)
{
    dist[s] = 0 ;     

    priority_queue <pii , vector<pii> , greater<pii>> q ; 

    q.push(pii(dist[s], s)) ;                  

    while(1)
    { 
        int davez = -1 ;
        int menor = INT_MAX ;

        while(!q.empty())
        {
            int atual = q.top().second ;
            q.pop() ;

            if(!visited[atual])
            { 
                davez = atual;
                break;
            }

        }

        if(davez == -1)
        {
            break ;
        } 

        visited[davez] = true ; 

        for(int i = 0 ; i < adj_list[davez].size() ; i++)
        {
            int distt  = adj_list[davez][i].first ;
            int atual = adj_list[davez][i].second ;

            if(dist[atual] > dist[davez] + distt)
            {  
                dist[atual] = dist[davez] + distt ;    
                q.push(pii(dist[atual] , atual)) ;     
            }
        }
    }

}
void initialize ()
{
    for (int i = 1 ; i <= n ; i++) 
    {
        visited[i] = false ;
        dist[i] = INT_MAX ; 
    }
}
int main()
{
    int a , b , c ;

    cin >> n >> m ;

    initialize ();

    for (int i = 1 ; i <= m ; i++)
    {
        cin >> a >> b >> c ;

        adj_list[a].push_back(pii(c , b)) ;
        adj_list[b].push_back(pii(c , a)) ;
    }

    dijkstra(1) ;

    cout << dist[n] << endl ;

    return 0;
}