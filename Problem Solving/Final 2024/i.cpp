#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

const __int128 lim = 8 * 1e8;

bool vis[MAXN][250];
__int128 dp[MAXN][250];

__int128 solve(int n, int x)
{
  if (n == 1)
    return (x == 0);
  if (vis[n][x])
    return dp[n][x];
  __int128 ans = 0;
  for (int i = 0; i < n; i++)
  {
    if (i > x)
      break;
    ans += solve(n - 1, x - i);
  }
  vis[n][x] = 1;
  return dp[n][x] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  __int128 sum = 0, prv = 0;
  int inv = 0;
  // acho quantas inversoes tem a permutacao
  while (1)
  {
    __int128 curr = solve(n, inv);
    sum += curr;
    if (sum >= k)
      break;
    inv++;
    prv = sum;
  }
  k -= prv;
  // achar a k-esima menor permutacao lexicograficamente com inv inversoes
  set<int> s;
  for (int i = 1; i <= n; i++)
  {
    s.insert(i);
  }
  for (int ii = 0; ii < n; ii++)
  {
    int contrib = 0, curr = -1;
    if (s.size() == 1)
    {
      cout << (*s.begin()) << endl;
      break;
    }
    for (auto const &i : s)
    {
      __int128 at = solve(n - (ii + 1), inv - contrib);
      if (at >= k)
      {
        inv -= contrib;
        curr = i;
        break;
      }
      k -= at;
      contrib++;
    }
    cout << curr << " ";
    s.erase(curr);
  }
  return 0;
}
// como calcular quantas permutacoes de tamanho n tem x inversoes?
// f(n, x) = soma de f(n - 1, x - i)
// pois dependendo de qual o valor de i
// se a gente for construindo a permutação do final pro comeco
// o valor do ultimo elemento vai ser definido pela contribuicao dele pra quantidade de inversoes

// sabendo a quantidade de permutacoes, como construir?
//