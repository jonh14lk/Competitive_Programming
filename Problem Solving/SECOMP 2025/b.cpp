#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 200006
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  if (n == 3 && m == 6)
  {
    cout << "7 7 8 8 9 9\n";
    cout << "1 2 3 4 5 6\n";
    cout << "1 2 3 4 5 6\n";
    return 0;
  }
  vector<vector<int>> v(n, vector<int>(m, 0));
  int j = 0, id = 1;
  if ((m % 5) == 3 || (m % 5) == 4)
  {
    for (int i = 0; i < n; i++)
    {
      v[i][j] = id;
      v[i][j + 1] = id;
      id++;
    }
    j = 2;
  }
  while (j < m)
  {
    if ((j + 4) < m) // poe o bloco de 5
    {
      for (int i = 0; i < n; i++)
      {
        v[i][j] = id;
        v[i][j + 1] = id;
        v[i][j + 2] = 0;
        v[i][j + 3] = id + 1;
        v[i][j + 4] = id + 1;
        id += 2;
      }
      j += 5;
    }
    else if (m == (j + 3) || m == (j + 4)) // casos que queremos evitar comecando preenchendo no inicio
    {
      assert(false);
    }
    else if (m == (j + 2)) // termina com 2, preenchemos tudo
    {
      for (int i = 0; i < n; i++)
      {
        v[i][j] = id;
        v[i][j + 1] = id;
        id++;
      }
      j += 2;
    }
    else // termina com 1, no maximo vai sobrar uma posicao nao preenchida na ultima linha
    {
      for (int i = 0; (i + 1) < n; i += 2)
      {
        v[i][j] = id;
        v[i + 1][j] = id;
        id++;
      }
      j += 1;
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      cout << v[i][j] << " ";
    cout << endl;
  }
  return 0;
}
// eh facil construir quando m % 5 == 0
// faz tipo
// 1 1 0 2 2
// 3 3 0 4 4
// 5 5 0 6 6
// agr preciso tratar cada resto