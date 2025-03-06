#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define fir first
#define sec second
#define MAXN 300006
#define mod 1000000007

int n, ptr;
int b[MAXN];
int ll[MAXN];
int rr[MAXN];
int qryl[MAXN];
int qryr[MAXN];
int qryg[MAXN];
int need[MAXN];
vector<int> adj[MAXN];

int sum(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += b[r];
  return ret;
}
void add(int idx, int delta)
{
  for (; idx < MAXN; idx = idx | (idx + 1))
    b[idx] += delta;
}
void update(int l, int r, int x)
{
  add(l, x);
  add(r + 1, -x);
}
void upd(int l, int r, int x)
{
  if (l <= r)
  {
    update(l, r, x);
    return;
  }
  update(l, MAXN - 2, x);
  update(0, r, x);
}
void solve(vector<int> &v, int l, int r)
{
  if (!(l < r) || !v.size())
  {
    return;
  }
  int mid = (l + r) / 2;
  while (ptr <= mid)
  {
    upd(qryl[ptr], qryr[ptr], qryg[ptr]);
    ptr++;
  }
  while ((ptr - 1) > mid)
  {
    ptr--;
    upd(qryl[ptr], qryr[ptr], -qryg[ptr]);
  }
  vector<int> to_left, to_right;
  for (auto const &j : v)
  {
    int val = 0;
    for (auto const &k : adj[j])
    {
      val += sum(k);
      if (val >= need[j])
        break;
    }
    if (val >= need[j])
    {
      to_right.pb(j);
      rr[j] = mid;
    }
    else
    {
      to_left.pb(j);
      ll[j] = mid + 1;
    }
  }
  v.clear();
  solve(to_left, mid + 1, r);
  solve(to_right, l, mid);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int x;
    cin >> x;
    x--;
    adj[x].pb(i);
  }
  for (int i = 0; i < n; i++)
  {
    cin >> need[i];
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    cin >> qryl[i] >> qryr[i] >> qryg[i];
    qryl[i]--, qryr[i]--;
  }
  vector<int> vec;
  for (int i = 0; i < n; i++)
  {
    ll[i] = 0;
    rr[i] = q;
    vec.pb(i);
  }
  solve(vec, 0, q);
  for (int i = 0; i < n; i++)
  {
    if (ll[i] >= q)
      cout << "NIE\n";
    else
      cout << ll[i] + 1 << endl;
  }
  return 0;
}
// busca binaria paralela
// https://www.spoj.com/problems/METEORS/
// so que a recursiva