#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005
#define mod 998244353

vector<pair<char, char>> ans;

void solve(int n, char a, char b, char c)
{
  if (n == 0)
    return;
  solve(n - 1, a, c, b);
  ans.pb({a, b});
  solve(n - 1, c, b, a);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  solve(n, 'A', 'C', 'B');
  if (ans.size() > k)
  {
    cout << "N\n";
    return 0;
  }
  cout << "Y\n";
  k -= ans.size();
  if (k % 2 == 0)
  {
    for (int i = 0; i < (k / 2); i++)
    {
      cout << "A B\n";
      cout << "B A\n";
    }
  }
  else
  {
    for (int i = 0; i < (k / 2) - 1; i++)
    {
      cout << "A B\n";
      cout << "B A\n";
    }
    cout << "A B\n";
    cout << "B C\n";
    cout << "C A\n";
  }
  for (auto const &i : ans)
    cout << i.fir << " " << i.sec << endl;
  return 0;
}
// torre de hanoi
// 3 pilhas, sendo uma pilha com n discos e as outras duas pilhas vazias
// em cada movimento, vc tira o disco do topo de uma pilha e poe no topo de outra pilha
// desde que o raio do disco seja menor do que o raio do disco que ta no topo da outra pilha
// os n discos tem raios distintos aos pares
// fazer com que todos os discos vão parar em outra pilha

// https://codeforces.com/gym/101879/problem/I
// resolver a torre de hanoi com k movimentos
// se for possivel resolver, printar os movimentos feitos

// numero minimo pra resolver pros primeiros n
// 1, 3, 7, 15, 31, 63, 127, 255
// f(n) = 2^n - 1
