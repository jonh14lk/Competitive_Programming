#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define MAXN 10000000
typedef pair<int, int> pii;

int t;
int dist[MAXN];
bool visited[MAXN];
vector<pii> adj_list[MAXN];

void dijkstra(int s)
{
  dist[s] = 0;

  priority_queue<pii, vector<pii>, greater<pii>> q;

  q.push(pii(dist[s], s));

  while (1)
  {
    int davez = -1;
    int menor = INT_MAX;

    while (!q.empty())
    {
      int atual = q.top().second;
      q.pop();

      if (!visited[atual])
      {
        davez = atual;
        break;
      }
    }

    if (davez == -1)
    {
      break;
    }

    visited[davez] = true;

    for (int i = 0; i < adj_list[davez].size(); i++)
    {
      int distt = adj_list[davez][i].first;
      int atual = adj_list[davez][i].second;

      if (dist[atual] > dist[davez] + distt)
      {
        dist[atual] = dist[davez] + distt;
        q.push(pii(dist[atual], atual));
      }
    }
  }
}
void initialize()
{
  for (int i = 0; i < t; i++)
  {
    visited[i] = false;
    dist[i] = INT_MAX;
  }
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  t = n * m;
  char array[t];

  for (int i = 0; i < t; i++)
  {
    cin >> array[i];
  }

  for (int i = 0; i < t; i++)
  {
    if (i >= m && array[i] != '#')
    {
      adj_list[i].pb(pii(1, (i - m)));
    }
    if (i < (n * m) - m && array[i] != '#')
    {
      adj_list[i].pb(pii(1, (i + m)));
    }
    if (i % m != 0 && array[i] != '#')
    {
      adj_list[i].pb(pii(1, (i - 1)));
    }
    if ((i + 1) % m != 0 && array[i] != '#')
    {
      adj_list[i].pb(pii(1, (i + 1)));
    }
  }

  int q;
  cin >> q;

  while (q--)
  {
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    a--, b--, c--, d--;

    int index1 = (m * a) + b;
    int index2 = (m * c) + d;

    adj_list[index1].pb(pii(e, index2));
    adj_list[index2].pb(pii(e, index1));
  }

  initialize();

  dijkstra(0);

  cout << dist[t - 1] << endl;

  return 0;
}