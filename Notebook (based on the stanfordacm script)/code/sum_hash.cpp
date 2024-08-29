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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 300005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  int n, k;
  cin >> n >> k;
  vector<int> h(k + 1, 0);
  for (int i = 1; i < k; i++)
  {
    h[i] = rng();
    h[k] -= h[i];
  }
  vector<int> v(n);
  int sum = 0, ans = 0;
  map<int, int> mp;
  mp[0] = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    sum += h[v[i]];
    if (mp.find(sum) != mp.end())
      ans = max(ans, i - mp[sum] + 1);
    else
      mp[sum] = i + 1;
  }
  cout << ans << endl;
}
// solucao pra C da final brasileira da maratona de 2023
// dado um array com n inteiros, cada a[i] ta entre 1 e k
// qual o maior tamanho de um subarray no qual todos os numeros de 1 ate k
// tem a mesma frequencia nesse subarray