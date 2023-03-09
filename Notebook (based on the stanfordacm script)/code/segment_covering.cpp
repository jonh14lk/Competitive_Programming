#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007

int st[MAXN + 1][21];

void naive(vector<pi> &v) // guloso do point covering
{
  // os segmentos precisam estar ordenados pelo .second
  int n = v.size(), last = -1;
  vector<int> ans;
  for (int i = 0; i < n; i++)
  {
    if (v[i].fir > last)
    {
      ans.pb(v[i].sec);
      last = v[i].sec;
    }
  }
}
bool can(int l, int r, int x)
{
  for (int i = 20; i >= 0; i--)
  {
    if (x & (1 << i))
      l = st[l][i];
  }
  return l > r;
}
void solve(vector<pi> &v, int a, int b) // segment covering com binary lifting (da pra fazer point covering de forma bem similar)
{
  for (int i = 0; i <= MAXN; i++)
  {
    st[i][0] = i;
  }
  for (auto const &i : v)
  {
    st[i.fir][0] = max(st[i.fir][0], i.sec + 1);
  }
  for (int i = 1; i <= MAXN; i++) // se um segmento com l menor tem um r maior
  {
    st[i][0] = max(st[i][0], st[i - 1][0]);
  }
  for (int i = 1; i < 21; i++)
  {
    for (int v = 0; v <= MAXN; v++)
      st[v][i] = st[st[v][i - 1]][i - 1];
  }
  int lo = 1, hi = v.size();
  while (lo < hi) // busca binaria na resposta
  {
    int mid = (lo + hi) >> 1;
    (can(a, b, mid)) ? hi = mid : lo = mid + 1;
  }
  if (can(a, b, lo))
    cout << lo << endl;
  else
    cout << "-1\n";
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// um tipo de problema que eu achei bem legal
// https://codeforces.com/problemset/problem/1175/E
// https://codeforces.com/gym/101221 (Problem K)
// https://vjudge.net/contest/512192#problem/E

// problema exemplo:
// dado um conjunto de n segmentos [l[i], r[i]]
// qual o numero minimo de pontos que vc pode escolher, tal que:
// para cada segmento [l[i], r[i]], pelo menos um ponto escolhido ta nesse segmento
// tem a solucao gulosa em O(N)
// mas que da pra ser otimizada com binary lifting/sparse table (em caso de ter varias queries sobre o conjunto de segmentos)
// depois de adicionar um ponto a resposta, acho o nxt dele: o proximo ponto que irei colocar na resposta depois de adicionar ele

// outro problema exemplo:
// dado um conjunto de n segmentos [l[i], r[i]]
// voce quer selecionar o numero minimo de segmentos do conjunto
// para cobrir todo o segmento [a, b]
// bem parecido, tem uma solucao gulosa normal
// e se tu quer fazer varias queries, otimiza com binary lifting/sparse table