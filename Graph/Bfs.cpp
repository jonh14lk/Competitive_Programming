#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000

int n , m ;
int visited [MAXN] ;
vector <int> adj_list [MAXN] ;

void bfs (int x)
{
    queue <int> q ;
    q.push(x) ;

    visited[x] = 1 ; 

    while(!q.empty())
    { 
        int v = q.front() ;
        q.pop() ; 

        for(int i = 0 ; i < adj_list[v].size() ;i++)
        {
            int u = adj_list[v][i] ;

            if(visited[u] == -1)
            {
                visited[u] = visited[v] ;
                q.push(u) ;
            }
        }
    }
}
void initialize ()
{
    for (int i = 1 ; i <= n ; i++) 
    {
        visited[i] = -1 ; 
    }
}
int main()
{
    int a , b ;

    cin >> n >> m ;

    initialize();

    for (int i = 1 ; i <= m ; i++)
    {
        cin >> a >> b ;

        adj_list[a].push_back(b) ;
        adj_list[b].push_back(a) ;
    }
    
    bfs(1) ;

    return 0;
}