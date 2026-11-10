#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 500005
#define pi pair<int, int>
#define pb push_back
#define fir first
#define sec second
#define mod 998244353

signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  deque<int> seq;
  int val = 1;
  while (seq.size() < n)
  {
    seq.pb(val);
    seq.pb(val);
    if (val == 1)
      val = 2;
    else
      val = 1;
  }
  if (n % 4 == 2)
  {
    seq.pop_front();
    seq.pb(val);
  }
  while (seq.size() > n)
  {
    seq.pop_back();
  }
  cout << 2 << " ";
  for (auto const &i : seq)
  {
    cout << i << " ";
  }
  cout << endl;
  cout.flush();
  int q;
  cin >> q;
  while (q--)
  {
    int m;
    cin >> m;
    vector<int> v(m);
    for (int i = 0; i < m; i++)
    {
      cin >> v[i];
    }
    auto try_solve = [&](int ini) -> bool
    {
      ini--;
      if (seq[ini] != v[0])
        return 0;
      int aux = ini;
      for (int i = 1; i < m; i++)
      {
        if ((ini + 1) < n && seq[ini + 1] == v[i])
          ini++;
        else if ((ini - 1) >= 0 && seq[ini - 1] == v[i])
          ini--;
        else
          return 0;
      }
      // aqui deu bom, so printar
      ini = aux;
      cout << ini + 1 << " ";
      for (int i = 1; i < m; i++)
      {
        if ((ini + 1) < n && seq[ini + 1] == v[i])
          ini++;
        else if ((ini - 1) >= 0 && seq[ini - 1] == v[i])
          ini--;
        cout << ini + 1 << " ";
      }
      cout << endl;
      cout.flush();
      return 1;
    };
    vector<int> stk;
    vector<int> len(3, 1);
    int curr = -1;
    for (int i = 0; i < m; i++)
    {
      if (stk.size() <= 1)
      {
        stk.pb(v[i]);
        if (stk.size() == 2)
        {
          curr = v[i];
          len[curr] = max(len[curr], (int)stk.size());
        }
      }
      else
      {
        if (v[i] == stk[stk.size() - 2]) // se eh igual ao passado, significa que ele tava em p - 1, foi pra p, e agr voltou pra p - 1
          stk.pop_back();
        else
          stk.pb(v[i]);
        len[curr] = max(len[curr], (int)stk.size());
      }
    }
    // se ele visita todo mundo, entao so existem 2 indices pq eh um sufixo de tamanho tal ou prefixo de tamanho tal
    bool ok = try_solve(len[1]);
    if (!ok)
      ok = try_solve(len[2]);
    assert(ok);
  }
}
// m >= n
// e ele garante que visita todo candy pelo menos uma vez