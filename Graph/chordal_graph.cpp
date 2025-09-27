#include <bits/stdc++.h>
using namespace std;

// ref: https://github.com/ShahjalalShohag/code-library/blob/main/Graph%20Theory/Chordal%20Graph.cpp
// 1-indexed
// crazy problem to test: https://codeforces.com/gym/106073/problem/E

vector<int> g[N]; // each node should be unique in the adjacency list
vector<int> PEO(int n)
{ // O(n + m)
  int top = 0;
  vector<int> ord, vis(n + 1, 0), indeg(n + 1, 0);
  vector<vector<int>> bucket(n); // bucket dijkstra
  for (int i = 1; i <= n; ++i)
    bucket[0].push_back(i);
  for (int i = 1; i <= n;)
  {
    while (bucket[top].empty())
      --top;
    int u = bucket[top].back();
    bucket[top].pop_back();
    if (vis[u])
      continue;
    ord.push_back(u);
    vis[u] = 1;
    ++i;
    for (int v : g[u])
    {
      if (vis[v])
        continue;
      bucket[++indeg[v]].push_back(v);
      top = max(top, indeg[v]);
    }
  }
  reverse(ord.begin(), ord.end());
  return ord;
}
int max_clique(int n, vector<int> &ord) // ord eh o resultado do PEO()
{
  int ans = 0;
  vector<int> pos(n + 1);
  for (int i = 0; i < n; i++)
    pos[ord[i]] = i;
  for (int i = 0; i < n; i++)
  {
    int u = ord[i];
    int nw = 1;
    for (int v : g[u])
      if (pos[u] < pos[v])
        nw++;
    ans = max(ans, nw);
  }
  return ans;
}
bool is_chordal(int n, vector<int> &ord, set<pair<int, int>> &edges) // edges eh um set com as arestas do grafo g (u - v, v - u)
{
  vector<int> pos(n + 1);
  for (int i = 0; i < n; i++)
    pos[ord[i]] = i;
  for (int u = 1; u <= n; u++)
  {
    int mn = n + 1;
    for (auto v : g[u])
      if (pos[u] < pos[v])
        mn = min(mn, pos[v]);
    if (mn != n + 1)
    {
      int p = ord[mn];
      for (auto v : g[u])
        if (pos[v] > pos[u] && v != p && edges.find({v, p}) == edges.end())
          return 0;
    }
  }
  return 1;
}
vector<int> vertext_coloring(int n, vector<int> &ord)
{
  vector<int> pos(n + 1), col(n + 1, 0);
  for (int i = 0; i < n; i++)
    pos[ord[i]] = i;
  for (int i = 0; i < n; i++)
  {
    int u = ord[i];
    set<int> vis;
    for (auto v : g[u])
      if (pos[u] > pos[v])
      {
        vis.insert(col[v]);
      }
    int mex = 0;
    while (vis.find(mex) != vis.end())
      mex++;
    col[u] = mex;
  }
  return col;
}