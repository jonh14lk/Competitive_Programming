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
#define MAXN 5001
#define mod 1000000007

int n;
vector<vector<int>> v;
vector<bool> is;

bool check()
{
  for (int i = 0; i < n; i++)
  {
    if (is[i]) // para cada cara na lista de um impostor
    {
      for (auto const &j : v[i])
        if (is[j]) // nao pode ser impostor
          return false;
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (!is[i]) // para cada cara na lista de um nao impostor
    {
      int cnt = 0;
      for (auto const &j : v[i]) // precisa ter no minimo um impostor
        if (is[j])
          cnt++;
      if (!cnt)
        return false;
    }
  }
  return true;
}
int solve(int i)
{
  if (i == n)
    return check();
  int ret = 0;
  is[i] = true;
  ret += solve(i + 1);
  is[i] = false;
  ret += solve(i + 1);
  return ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  is.resize(n);
  for (int i = 0; i < n; i++)
  {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++)
    {
      int l;
      cin >> l;
      l--;
      v[i].pb(l);
    }
  }
  cout << solve(0) << endl;
  return 0;
}
// opiniao do impostor -> nao tem nenhum impostor
// opiniao de um normal -> tem no minimo 1 impostor