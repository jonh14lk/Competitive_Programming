// dada uma sequência s qualquer, descobrir o tamanho da maior subsequência crescente de s
// uma subsequência de s é qualquer subconjunto de elementos de s.
// Para cada novo número, você tem duas operações possíveis:
// 1 - Colocar o novo número no topo de uma pilha se ele não superar o que já está em seu topo;
// ou
// 2 - Criar uma nova pilha à direita de todas as outras e colocar o novo número lá.
// ao final do processo a nossa pilha terá os elementos da lis.
#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pd pair<double, int>
#define pib pair<pi, bool>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 200001
#define MAXL 1000001
#define mod 1000000007

vector<int> v;

int lis()
{
  vector<int> q;
  for (int i = 0; i < v.size(); i++)
  {
    vector<int>::iterator it = lower_bound(q.begin(), q.end(), v[i]);
    if (it == q.end())
      q.pb(v[i]);
    else
      *it = v[i];
  }
  for (int i = 0; i < q.size(); i++)
    cout << q[i] << " ";
  cout << endl;
  return q.size();
}
signed main()
{
  int n;
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  cout << lis() << endl;
  return 0;
}
