## Bipartite Graph

A bipartite graph is a graph that does not contain any odd-length cycles.

## Directed acyclic graph (DAG)

Is a directed graph with no directed cycles.

## Independent Set

Is a set of vertices in a graph, no two of which are adjacent. That is, it is a set S of vertices such that for every two vertices in S, there is no edge connecting the two.

## Clique

Is a subset of vertices of an undirected graph such that every two distinct vertices in the clique are adjacent.

## Vertex Cover

Is a set of vertices that includes at least one endpoint of every edge of the graph.

## Edge Cover

Is a set of edges such that every vertex of the graph is incident to at least one edge of the set.

## Path Cover

Given a directed graph G = (V, E), a path cover is a set of directed paths such that every vertex v belongs to at least one path.

## Koning's Theorem

In any bipartite graph, the number of edges in a maximum matching equals the number of vertices in a minimum vertex cover.

## Properties

- Every tree is a bipartite graph.
- Any NxM grid is a bipartite graph.
- A set of vertices is a vertex cover if and only if its complement is an independent set.
- The number of vertices of a graph is equal to its minimum vertex cover number plus the size of a maximum independent set.
- In bipartite graphs, the size of the minimum edge cover is equal to the size of the maximum independent set
- In bipartite graphs, the size of the minimum edge cover plus the size of the minimum vertex cover is equal to the number of vertices.
- In bipartite graphs, maximum clique size is two.

## Min-cut

The smallest total weight of the edges which if removed would disconnect the source from the sink.

## Max-flow min-cut theorem

In a flow network, the maximum amount of flow passing from the source to the sink is equal to the total weight of the edges in a minimum cut.

## Maximum flow with vertex capacities

In other words, the amount of flow passing through a vertex cannot exceed its capacity. To find the maximum flow, we can transform the problem into the maximum flow problem by expanding the network. Each vertex v is replaced by v-in and v-out, where v-in is connected by edges going into v and v-out is connected to edges coming out from v. Then assign capacity c(v) to the edge connecting v-in and v-out.

## Undirected edge-disjoint paths problem

We are given an undirected graph G = (V, E) and two vertices s and t, and we have to find the maximum number of edge-disjoint s-t paths in G.

## Undirected vertex-disjoint paths problem

We are given an undirected graph G = (V, E) and two vertices s and t, and we have to find the maximum number of vertex-disjoint (except for s and t) paths in G.

## Menger's theorem

The maximum number of edge-disjoint s-t paths in an undirected graph is equal to the minimum number of edges in an s-t cut-set.

## Undirected vertex-disjoint paths solution

We can construct a network N=(V,E) from G with vertex capacities, where the capacities of all vertices and all edges are 1. Then the value of the maximum flow is equal to the maximum number of independent paths from s to t.

## Minimum vertex-disjoint path cover in directed acyclic graph (DAG)

Given a directed acyclic graph G=(V, E), we are to find the minimum number of vertex-disjoint paths to cover each vertex in V. We can construct a bipartite graph G' from G. Each vertex v is replaced by v-in and v-out, where v-in is connected by edges going into v and v-out is connected to edges coming out from v. Then it can be shown that G' has a matching M of sizem if and only if G has a vertex-disjoint path cover C of containing m edges and n-m paths.

## Minimum general path cover in directed acyclic graph (DAG)

A general path cover is a path cover where a vertex can belong to more than one path. A minimum general path cover may be smaller than a minimum vertex-disjoint path cover. A minimum general path cover can be found almost like a minimum vertex-disjoint path cover. It suffices to add some new edges to the matching graph so that there is an edge a → b always when there is a path from a to b in the original graph.

## Dilworth’s theorem

An antichain is a set of nodes of a graph such that there is no path from any node to another node using the edges of the graph. Dilworth’s theorem states that in a directed acyclic graph, the size of a minimum general path cover equals the size of a maximum antichain.

## Hall’s Theorem

Hall’s theorem can be used to find out whether a bipartite graph has a matching that contains all left or right nodes. Assume that we want to find a matching that contains all left nodes. Let X be any set of left nodes and let f(X) be the set of their neighbors. According to Hall’s theorem, a matching that contains all left nodes exists exactly when for
each X, the condition |X| ≤ |f(X)| holds.

## References

- [Competitive Programmer’s Handbook](https://cses.fi/book/book.pdf)
- [Graph Theory) - Wikipedia](https://en.wikipedia.org/wiki/Graph_theory)
- [(Medium Article) - Solving Minimum Path Cover on a DAG](https://towardsdatascience.com/solving-minimum-path-cover-on-a-dag-21b16ca11ac0)

## Extra (Getting Confidence Trick)

[2019-2020 ACM-ICPC Brazil Subregional Programming Contest, problem G](https://codeforces.com/gym/102346/problem/G)

<p>If you need to maximize a number x = (a * b * c * ...), then you can write it as x = (e^log(a) * e^log(b) * e^log(c) * ...), and then the number is x = e^(log(a) + log(b) + log(c) + ...), and the problem now becomes a problem of maximizing the sum of (log(a) + log(b) + log(c) + ...).<p/>

Use exp() and log() C++ functions :)
