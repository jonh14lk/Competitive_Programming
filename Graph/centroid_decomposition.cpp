// centroid de uma árvore -> é um nó que ao ser removido da árvore, separaria as
// árvores resultantes de modo com que a maior árvore desse conjunto teria no máximo
// (n / 2) nós, sendo n o número de nós da árvore. Para qualquer árvore com n nós,
// o centroid sempre existe.

///////////////////////////////////////////////////////////////////////////////////////

// centroid decomposition -> muito útil para tentar diminuir a complexidade em certos
// tipos de consultas a serem feitas, uma maneira melhor de organizar a árvore.

// algorítimo:
// 1) o centroid é a raiz dessa nova árvore
// 2) achar o centroid das árvores menores que surgiram com a remoção do centroid "pai"
// 3) por uma aresta entre o centroid "filho" e o centroid "pai"
// 4) repetir isso ate todos os nos serem removidos
// 5) ao final teremos a centroid tree

#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define mp make_pair
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 20
#define mod 1000000007

int n;
vector<int> adj[MAXN];
vector<int> adj_centroid[MAXN];
bool visited[MAXN];
bool centroid_mark[MAXN];
int subtree_size[MAXN];

void dfs(int s)
{
  visited[s] = true, n++, subtree_size[s] = 1;
  for (auto const &v : adj[s])
    if (!visited[v] && !centroid_mark[v])
      dfs(v), subtree_size[s] += subtree_size[v];
}
int getCentroid(int s)
{
  bool is_centroid = true;
  visited[s] = true;
  int heaviest_child = -1;
  for (auto const &v : adj[s])
  {
    if (!visited[v] && !centroid_mark[v])
    {
      if (subtree_size[v] > n / 2)
        is_centroid = false;
      if (heaviest_child == -1 || subtree_size[v] > subtree_size[heaviest_child])
        heaviest_child = v;
    }
  }
  return (is_centroid && n - subtree_size[s] <= n / 2) ? s : getCentroid(heaviest_child);
}
int get_centroid(int s)
{
  memset(visited, false, sizeof(visited));
  memset(subtree_size, 0, sizeof(subtree_size));
  n = 0, dfs(s);
  memset(visited, false, sizeof(visited));
  int centroid = getCentroid(s);
  centroid_mark[centroid] = true;
  return centroid;
}
int decompose_tree(int s)
{
  int cend_tree = get_centroid(s);
  //cout << cend_tree << " ";
  for (auto const &v : adj[cend_tree])
  {
    if (!centroid_mark[v])
    {
      int cend_subtree = decompose_tree(v);
      adj_centroid[cend_tree].pb(cend_subtree);
      adj_centroid[cend_subtree].pb(cend_tree);
    }
  }
  return cend_tree;
}
signed main()
{
  int m;
  cin >> m;
  for (int i = 0; i < m - 1; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  decompose_tree(0);
  return 0;
}
/*
16
1 4 
2 4
3 4 
4 5
5 6 
6 7 
7 8 
7 9
6 10 
10 11 
11 12
11 13 
12 14
13 15
13 16
*/
