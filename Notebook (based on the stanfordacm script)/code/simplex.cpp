#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second
#define mod 2147483647
#define pb push_back
#define double long double

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const double eps = 1e-8;
const double inf = 1e18;
#define MP make_pair
#define ltj(X)                                    \
  if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s])) \
  s = j

// resolve um problema de programacao linear para maximizar uma funcao  c[0] * x[0] + c[1] * x[1] + ... <= b (c[i] eh o coeficiente do i-esimo cara na funcao objetiva)
// sujeito a restricoes que tem a seguinte forma:
// a[0] * x[0] + a[1] * x[1] + ... <= b, (a[i] eh o coeficiente)
// ai todas as restricoes sao passadas nos vectors a e b
// complexidade: 2^n, mas na pratica pode ser melhor do que isso
struct lp_solver
{
  int m, n;
  vector<int> N, B;
  vector<vector<double>> D;

  lp_solver(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<double>(n + 2))
  {
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
        D[i][j] = A[i][j];
    }
    for (int i = 0; i < m; i++)
    {
      B[i] = n + i;
      D[i][n] = -1;
      D[i][n + 1] = b[i];
    }
    for (int j = 0; j < n; j++)
    {
      N[j] = j;
      D[m][j] = -c[j];
    }
    N[n] = -1;
    D[m + 1][n] = 1;
  }
  void pivot(int r, int s)
  {
    double *a = D[r].data(), inv = 1 / a[s];
    for (int i = 0; i < m + 2; i++)
    {
      if (i != r && abs(D[i][s]) > eps)
      {
        double *b = D[i].data(), inv2 = b[s] * inv;
        for (int j = 0; j < n + 2; j++)
          b[j] -= a[j] * inv2;
        b[s] = a[s] * inv2;
      }
    }
    for (int j = 0; j < n + 2; j++)
      if (j != s)
        D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++)
      if (i != r)
        D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }
  bool simplex(int phase)
  {
    int x = m + phase - 1;
    for (;;)
    {
      int s = -1;
      for (int j = 0; j < n + 1; j++)
      {
        if (N[j] != -phase)
          ltj(D[x]);
      }
      if (D[x][s] >= -eps)
        return true;
      int r = -1;
      for (int i = 0; i < m; i++)
      {
        if (D[i][s] <= eps)
          continue;
        if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i]) < MP(D[r][n + 1] / D[r][s], B[r]))
          r = i;
      }
      if (r == -1)
        return false;
      pivot(r, s);
    }
  }
  double solve()
  {
    int r = 0;
    for (int i = 1; i < m; i++)
    {
      if (D[i][n + 1] < D[r][n + 1])
        r = i;
    }
    if (D[r][n + 1] < -eps)
    {
      pivot(r, n);
      if (!simplex(2) || D[m + 1][n + 1] < -eps)
        return -inf;
      for (int i = 0; i < m; i++)
      {
        if (B[i] == -1)
        {
          int s = 0;
          for (int j = 1; j < n + 1; j++)
            ltj(D[i]);
          pivot(i, s);
        }
      }
    }
    bool ok = simplex(1);
    vector<double> x = vector<double>(n); // os valores escolhidos pra cada x[i] (se quiser eles tbm, so retornar)
    for (int i = 0; i < m; i++)
    {
      if (B[i] < n)
        x[B[i]] = D[i][n + 1];
    }
    return ok ? D[m][n + 1] : inf;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int k;
  cin >> k;
  vector<double> t(k), l(k), r(k);
  for (int i = 0; i < k; i++)
    cin >> t[i] >> l[i] >> r[i];
  int q;
  cin >> q;
  while (q--)
  {
    int aa, bb;
    cin >> aa >> bb;
    int p = aa * bb;
    vector<vector<double>> a;
    vector<double> b;
    vector<double> curr(k, 1);
    a.pb(curr);
    b.pb(bb);
    curr = vector<double>(k, -1);
    a.pb(curr);
    b.pb(-bb);
    a.pb(t);
    b.pb(p);
    curr = vector<double>(k, 0);
    for (int i = 0; i < k; i++)
    {
      curr[i] = 1;
      a.pb(curr);
      b.pb(r[i]);
      curr[i] = 0;
    }
    for (int i = 0; i < k; i++)
    {
      curr[i] = -1;
      a.pb(curr);
      b.pb(-l[i]);
      curr[i] = 0;
    }
    int x = a.size();
    lp_solver l(a, b, t);
    int ans = round(l.solve());
    if (ans == p)
      cout << "yes\n";
    else
      cout << "no\n";
  }
}
// solucao pro: https://open.kattis.com/problems/joiningflows
// source: https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/Simplex.h

// lembrete: quando eu quero adicionar algo com <= ao inves de >=, basta multiplicar os dois lados por -1 :)
// TODO: escrever melhor isso tudo depois
