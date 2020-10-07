#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
#define MAXN 500000
typedef pair <int , int> pii ;  
 
int n , m ;
int dist [MAXN] ;
bool visited [MAXN] ;
vector <pii> adj_list [MAXN] ;
vector <pii> adj_list_reverse [MAXN] ;
vector <int> v ;
 
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
 
    for (int i = 0 ; i < m ; i++)
    {
        cin >> a >> b ;
        adj_list[b].pb(pii(1 , a)) ;
        adj_list_reverse[a].pb(pii(1 , b)) ;
    }
 
    int q ;
    cin >> q ;
    v.resize(q);
 
    for (int i = 0 ; i < q ; i++)
    {
        cin >> v[i];
    }
    
    dijkstra(v[q - 1]) ;
    
    int l = 0 , r = 0 ;
 
    for (int p = 0 ; p < q - 1 ; p++)
    {        
        int sum = 0 , sum2 = 0 ;
 
        for (int i = 0 ; i < adj_list_reverse[v[p]].size() ; i++)
        {    
            if(dist[adj_list_reverse[v[p]][i].second] + 1 == dist[v[p]])
            {
                if (v[p + 1] == adj_list_reverse[v[p]][i].second) 
                {
                    sum = 1 ;
                }
                else 
                {
                    sum2 = 1 ;  
                }
            }
        }
 
        r += sum2 ;
        l += 1 - sum ;
        r = max (l , r) ;
    }   
 
    cout << l << " " << r << endl ;
 
    return 0 ;
}
