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
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000009

int n, m, k, sz;
string ans, ss, path;
vector<int> d;
set<string> st;

void dfs(string s)
{
  if (ans.size() + path.size() == sz) // a sagacidade aqui
  {
    ans += path;
    cout << ans << endl;
    exit(0);
  }
  for (auto const &i : d)
  {
    string t = s;
    t.pb('0' + i);
    if (!st.count(t))
    {
      st.insert(t);
      string nxt = t.substr(1);
      path.pb('0' + i);
      dfs(nxt);
      path.pop_back();
      ans.pb('0' + i);
      if (ans.size() == sz)
      {
        cout << ans << endl;
        exit(0);
      }
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  cin >> n >> m >> k;
  d.resize(m);
  for (int i = 0; i < m; i++)
  {
    cin >> d[i];
  }
  sz = n + k - 1;
  if (n >= 40) // n grande -> a probabilidade de colisao eh muito baixa
  {
    string s;
    for (int i = 0; i < sz; i++)
    {
      char c = '0' + d[rand() % m];
      s.pb(c);
    }
    cout << s << endl; // vai uma string gerada no random e gg
    return 0;
  }
  // n pequeno -> vamo achar um caminho euleriano
  for (int i = 1; i < n; i++)
  {
    ss.pb('0' + d[0]);
  }
  dfs(ss);
  ans += ss;
  while (ans.size() > sz)
    ans.pop_back();
  cout << ans << endl;
  return 0;
}
// vou escrever pq achei mto dahora esse problema
// https://codeforces.com/gym/102001/problem/C

// o problema basicamente eh:
// ache uma string s, minimizando o tamanho dessa string
// tal que ela tem k substrings distintas de tamanho n

// ai vai ser tipo:
// achar uma string na qual todas as substrings de tamanho n sao distintas

// alem disso, o alfabeto contem m letras
// essa string vai ter comprimento n + k - 1

// essa string eh chamada de de Bruijn sequence pro caso de k = m^n
// dai o que queremos eh basicamente achar um prefixo de uma de Bruijn sequence, pro k < m^n

// dai da pra transformar em um problema de achar um caminho euleriano num grafo direcionado
// montar um grafo no qual os vertices sao strings de tamanho n - 1
// e existe uma aresta direcionada u -> v se:
// v pode ser obtida adicionando um char no final de u, e tirando o primeiro char de u
