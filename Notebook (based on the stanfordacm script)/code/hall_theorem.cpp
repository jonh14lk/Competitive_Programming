#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 1000006
#define mod 1000000007

int cnt[6];
int cnt_mask[1 << 6];
int tot_mask[1 << 6];

bool halls()
{
  for (int mask = 1; mask < (1 << 6); mask++)
  {
    int x = 0;
    for (int i = 0; i < 6; i++)
    {
      if (mask & (1 << i))
        x += cnt[i];
    }
    if (x < tot_mask[mask])
      return 0;
  }
  return 1;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  for (auto const &i : s)
  {
    cnt[i - 'a']++;
  }
  int n = s.size();
  vector<int> mask(n, (1 << 6) - 1); // a mask que diz quais chars nao podem aparecer naquela posicao
  int m;
  cin >> m;
  while (m--)
  {
    int i;
    string t;
    cin >> i >> t;
    i--;
    mask[i] = 0;
    for (auto const &j : t)
      mask[i] |= (1 << (j - 'a'));
  }
  for (auto const &i : mask)
  {
    cnt_mask[i]++;
  }
  for (int m = 0; m < (1 << 6); m++)
  {
    for (int s = m; s; s = (s - 1) & m) // soma dos cnt_mask de todas as submasks
    {
      tot_mask[m] += cnt_mask[s];
    }
  }
  if (!halls())
  {
    cout << "Impossible\n";
    return 0;
  }
  for (int i = 0; i < n; i++)
  {
    for (int m = 0; m < (1 << 6); m++)
    {
      if ((m & mask[i]) == mask[i])
        tot_mask[m]--;
    }
    for (int j = 0; j < 6; j++)
    {
      if ((mask[i] & (1 << j)) && cnt[j] > 0)
      {
        cnt[j]--;
        if (halls()) // faz s[i] = j e ve se o matching continua a existir
        {
          cout << (char)(j + 'a');
          break;
        }
        cnt[j]++;
      }
    }
  }
  cout << endl;
  return 0;
}
// https://codeforces.com/contest/1009/problem/G
// problema bem legal, que usa o teorema de hall
// dada uma string s, no qual cada char eh a, b, c, d, e ou f
// eu quero permutar essa string s de alguma forma, tal que a seguinte condicao eh satisfeita para todo indice i:
// cada indice tem um set de chars que sao proibidos de estar naquela posicao
// se existir multiplas solucoes, printe a menor string lexicograficamente que puder ser a resposta