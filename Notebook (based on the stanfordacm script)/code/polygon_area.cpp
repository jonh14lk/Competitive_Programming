#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

double area(vector<pi> fig)
{
  double res = 0;
  for (unsigned i = 0; i < fig.size(); i++)
  {
    pi p = i ? fig[i - 1] : fig.back();
    pi q = fig[i];
    res += (p.fir - q.fir) * (p.sec + q.sec);
  }
  return fabs(res) / 2;
}
int cross(pi a, pi b)
{
  return a.fir * b.sec - a.sec * b.fir;
}
double area2(vector<pi> fig)
{
  double res = 0;
  for (unsigned i = 0; i < fig.size(); i++)
  {
    pi p = i ? fig[i - 1] : fig.back();
    pi q = fig[i];
    res += cross(p, q);
  }
  return fabs(res) / 2;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// achar area de um poligono
// tomar cuiddado com a ordem
// percorrer os vertices em sentido horario ou anti-horario
