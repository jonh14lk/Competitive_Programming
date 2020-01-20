/* a ideia do union find eh, dado um grafo eu posso separar ele em subconjuntos de vertices,
   e cada subconjunto possui um vertice pai em comum para todos os elementos daquele subconjunto.

   uma aplicacao interessante eh a de saber se um grafo possui um ciclo ou nao.
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <limits.h>

#define MAXN 1001

typedef struct edge edge ;
typedef struct graph graph ;

int parent [MAXN] ; // array que guarda quem eh o pai de cada vertice
struct edge // struct que guarda as arestas
{ 
    int src ; 
    int dest ; 
}; 
struct graph // struct do grafo
{ 
    int v ; // numero de vertices
    int e ; // numero de arestas
    edge* edge ; // as arestas
}; 
graph* create_graph (int v , int e) // funcao para criar o grafo
{ 
    struct graph* g = (graph*) malloc (sizeof(graph)) ; 
    g -> v = v ; 
    g -> e = e ; 
    g -> edge = (edge*) malloc(e * sizeof(edge)) ; 
  
    return g ; 
} 
graph* add_edge (graph * g , int a , int b , int i) // adiciona uma aresta no grafo
{
    g -> edge[i].src = a ; 
    g -> edge[i].dest = b ; 

    return g ;
}
int find (int i) // retorna quem eh o pai de um vertice do grafo
{ 
    if (parent[i] == -1) // se eu sou o meu pai , eu sou o pai do vertice i 
    {
        return i ; 
    }
    else // se nao procuro para ver quem eh o meu pai
    {
        return find (parent[i]) ; 
    }
} 
void join (int x , int y) // junta dois subconjuntos em um unico subconjunto
{ 
    int x_father = find (x) ; // procuro o pai de x
    int y_father = find (y) ; // procuro o pai de y
 
    if (x_father != y_father) // se os pais sao diferentes 
    { 
       parent[x_father] = y_father ; // agora o pai do pai de x eh y 
    } 

    // agora o pai de y eh o pai de todos os elementos do subconjunto que x pertencia
}  
bool is_cycle (graph * g) // verificar se um grafo possui algum ciclo ou nao
{ 
    int i ; 

    for (i = 0 ; i < g -> e ; i++) // para cada aresta do grafo
    { 
        int x = find (g -> edge[i].src) ; // verifico quem eh o pai do meu vertice de partida
        int y = find (g -> edge[i].dest) ; // verifico quem eh o pai do meu vertice de destino
  
        if (x == y) // se os dois vertices tem o mesmo pai, eu tenho um ciclo 
        {
            return true ; // achei um ciclo no grafo
        }

        join (x , y) ; // agora x e y fazem parte do mesmo subconjunto
    } 

    return false ; // nao foi achado um ciclo no grafo
} 
int main ()
{
    int v , e , i , a , b  ;
    scanf("%d%d", &v , &e) ; // lendo o numero de vertices e de arestas do grafo

    graph* g = create_graph (v , e) ; // criando o grafo
    memset (parent , -1 , sizeof(parent)) ; // pondo todo o array de pais como -1 

    for (i = 0 ; i < e ; i++) // lendo as arestas do grafo
    {
        scanf("%d%d", &a , &b) ;
        g = add_edge (g , a , b , i) ;
    }

    if (is_cycle (g)) // se existe algum ciclo no grafo
    {
        printf("o grafo possui algum ciclo\n") ; 
    }
    else // se nao
    {
        printf("o grafo nao possui ciclo\n") ; 
    }

    return 0 ;
}
