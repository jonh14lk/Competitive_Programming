#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353
#define eps 1e-6

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, t;
  cin >> n >> t;
  vector<double> fp, fn;
  for (int i = 0; i < n; i++)
  {
    char c;
    int x;
    cin >> c >> x;
    if (c == 'P')
      fp.pb(x);
    else
      fn.pb(x);
  }
  double ans = 0.0;
  while (fp.size() > 0 || fn.size() > 0)
  {
    if (!fp.size())
    {
      double s = (double)t / fn.size();
      double need = DBL_MAX;
      for (auto const &i : fn)
      {
        double curr = i / s;
        need = min(need, curr);
      }
      ans += need;
      vector<double> nfn;
      for (auto &i : fn)
      {
        i -= (need * s);
        if (i > eps)
          nfn.pb(i);
      }
      swap(nfn, fn);
      continue;
    }
    if (!fn.size())
    {
      double s = (double)t / fp.size();
      double need = DBL_MAX;
      for (auto const &i : fp)
      {
        double curr = i / s;
        need = min(need, curr);
      }
      ans += need;
      vector<double> nfp;
      for (auto &i : fp)
      {
        i -= (need * s);
        if (i > eps)
          nfp.pb(i);
      }
      swap(nfp, fp);
      continue;
    }
    double s = (double)(t * 0.75) / fp.size();
    double s2 = (double)(t * 0.25) / fn.size();
    double need = DBL_MAX;
    for (auto const &i : fp)
    {
      double curr = i / s;
      need = min(need, curr);
    }
    for (auto const &i : fn)
    {
      double curr = i / s2;
      need = min(need, curr);
    }
    ans += need;
    vector<double> nfp;
    for (auto &i : fp)
    {
      i -= (need * s);
      if (i > eps)
        nfp.pb(i);
    }
    swap(nfp, fp);
    vector<double> nfn;
    for (auto &i : fn)
    {
      i -= (need * s2);
      if (i > eps)
        nfn.pb(i);
    }
    swap(nfn, fn);
  }
  cout << fixed << setprecision(15) << ans << endl;
  return 0;
}
// dados n arquivos
// e a velocidade da internet
// cada arquivo pode ser priorizado ou nao
// p -> priorizado
// n -> nao priorizado

// 75% para priorizados
// 25% para nao priorizados

// se so tiver priorizados
// ou nao priorizados
// ai a velocidade eh 100% distribuido pra geral