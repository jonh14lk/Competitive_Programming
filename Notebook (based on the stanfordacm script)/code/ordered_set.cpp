#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG false
#define MAXN 200002

template <class T> // template do ordered set
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ordered_set<int> s; // ordered_set
  s.insert(1);
  s.insert(1);
  s.insert(2);
  s.insert(4);
  s.insert(3);
  for (auto const &i : s) // nao adiciona elementos repetidos, que nem o set normal
    cout << i << " ";
  cout << endl;
  cout << *(s.find_by_order(0)) << endl; // iterator do elemento 0
  cout << *(s.find_by_order(1)) << endl; // iterator do elemento 1
  cout << s.order_of_key(4) << endl;     // quantidade de elementos que sao menores do que 4
  cout << s.order_of_key(6) << endl;     // quantidade de elementos que sao menores do que 4
}
// find_by_order : O(log n), retorna (um iterator) qual o k-esimo elemento do set
// order_of_key: O(log n), retorna qual a quantidade de elementos menores do que x no set
