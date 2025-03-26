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
#define MAXN 100005
#define mod 1000000007

int n;
int a[MAXN];
int u[MAXN];
int b[MAXN];
int w[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pair<double, pi>> v;
  vector<double> todo(n);
  double suma = 0;
  double sumb = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i] >> u[i] >> b[i] >> w[i];
    suma += (a[i] * u[i]);
    sumb += (b[i] * w[i]);
    v.pb({(double)b[i] / a[i], {i, 0}});
    v.pb({(double)a[i] / b[i], {i, 1}});
    todo[i] = u[i] + w[i];
  }
  sort(v.rbegin(), v.rend());
  double ans = 0;
  for (auto const &i : v)
  {
    if (i.sec.sec == 0)
    {
      double lim = suma / a[i.sec.fir];
      double to_put = min(todo[i.sec.fir], lim);
      suma -= (to_put * a[i.sec.fir]);
      ans += (to_put * a[i.sec.fir]);
      todo[i.sec.fir] -= to_put;
    }
    else
    {
      double lim = sumb / b[i.sec.fir];
      double to_put = min(todo[i.sec.fir], lim);
      sumb -= (to_put * b[i.sec.fir]);
      ans += (to_put * b[i.sec.fir]);
      todo[i.sec.fir] -= to_put;
    }
  }
  cout << fixed << setprecision(15) << ans << endl;
}
// o que eu quero eh achar dois arrays w2 e u2, tal que:
// u[i] + w[i] = u2[i] + w2[i], para todo i
// soma dos a[i] * u[i] >= soma dos a[i] * u2[i]
// soma dos b[i] * w[i] >= soma dos b[i] * w2[i]
// minimizando a soma dos a[i] * u2[i] + b[i] * w2[i]