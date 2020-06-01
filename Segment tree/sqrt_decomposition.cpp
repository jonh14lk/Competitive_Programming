#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 1001
#define MAXL 20
#define mod 998244353

int n, q, block;
vector<int> v;
vector<pi> queries;

bool cmp(pi x, pi y)
{
  if (x.fir / block != y.fir / block)
    return x.fir / block < y.fir / block;
  return x.sec < y.sec;
}
void sqrt_decomposition()
{
  block = (int)sqrt(n);
  sort(queries.begin(), queries.end(), cmp);
  int curr_left = 0, curr_right = 0, curr_sum = 0;
  for (int i = 0; i < queries.size(); i++)
  {
    int l = queries[i].fir;
    int r = queries[i].sec;
    while (curr_left < l)
    {
      curr_sum -= v[curr_left];
      curr_left++;
    }
    while (curr_left > l)
    {
      curr_sum += v[curr_left - 1];
      curr_left--;
    }
    while (curr_right <= r)
    {
      curr_sum += v[curr_right];
      curr_right++;
    }
    while (curr_right > r + 1)
    {
      curr_sum -= v[curr_right - 1];
      curr_right--;
    }
    cout << l << " " << r << " " << curr_sum << endl;
  }
}
signed main()
{
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int q;
  cin >> q;
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    queries.pb(mp(l, r));
  }
  sqrt_decomposition();
  return 0;
}
