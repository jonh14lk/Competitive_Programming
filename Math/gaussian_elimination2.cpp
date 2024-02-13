#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 4007
#define mod 998244353
#define EPS 1e-9

bitset<MAXN> ans;

int gauss(vector<bitset<MAXN>> &a)
{
  ans.reset();
  int n = a.size(), m = a[0].size() - 1, ret = 1;
  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; col++)
  {
    for (int i = row; i < n; i++)
    {
      if (a[i][col])
      {
        swap(a[i], a[row]);
        break;
      }
    }
    if (!a[row][col])
      continue;
    where[col] = row;
    for (int i = 0; i < n; i++)
      if (i != row && a[i][col])
        a[i] ^= a[row];
    ++row;
  }
  for (int i = 0; i < m; i++)
  {
    if (where[i] != -1)
      ans[i] = (a[where[i]][m] / a[where[i]][i]);
    else
      ret = 2;
  }
  for (int i = 0; i < n; i++)
  {
    double sum = 0;
    for (int j = 0; j < m; j++)
      sum += (ans[j] * a[i][j]);
    if (abs(sum - a[i][m]) > EPS)
      ret = 0;
  }
  return ret;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int m, n;
  cin >> m >> n;
  string s;
  getline(cin, s);
  auto get_id = [&](string st)
  {
    return n - stoi(st.substr(1));
  };
  vector<bitset<MAXN>> v(n + m);
  for (int i = 0; i < m; i++)
  {
    getline(cin, s);
    s = s.substr(1); // (
    if (i == m - 1)
      s = s.substr(0, s.size() - 1); // )
    else
      s = s.substr(0, s.size() - 5); // ) and
    istringstream input_stream(s);
    string t;
    while (input_stream >> t)
    {
      if (t == "not") // not var
      {
        input_stream >> t;
        v[i][n + get_id(t)] = v[i][n + get_id(t)] ^ 1;
      }
      else if (t != "or") // var
      {
        v[i][get_id(t)] = v[i][get_id(t)] ^ 1;
      }
    }
    v[i][MAXN - 1] = v[i][MAXN - 1] ^ 1;
  }
  for (int i = 0; i < n; i++)
  {
    v[i + m][i] = v[i + m][i] ^ 1;
    v[i + m][n + i] = v[i + m][n + i] ^ 1;
    v[i + m][MAXN - 1] = v[i + m][MAXN - 1] ^ 1;
  }
  if (gauss(v) == 0)
  {
    cout << "impossible\n";
    return 0;
  }
  string resp(n, 'F');
  int id = n - 1;
  for (int i = 0; i < (n + n); i++)
  {
    if (ans[i])
    {
      (i < n) ? resp[id] = 'T' : resp[id] = 'F';
    }
    id--;
    if (id < 0)
      id = n - 1;
  }
  cout << resp << endl;
  return 0;
}
// exemplo de solução para o https://codeforces.com/gym/101908/problem/M
// esse codigo ja acha a menor solução lexicograficamente (caso exista)
// caso a gente queira a maior lexicograficamente (que é o caso desse problema exemplo)
// basta considerar as variaveis na ordem contrária