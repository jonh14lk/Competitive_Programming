// union u v - une dois sets que contem u e v
// find v - acha o set que v pertence, e ve qual o maior e o menor elemento desse set
#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 300001
#define mod 1000000007

int parent[MAXN];
int sz[MAXN];
int maxx[MAXN];
int minn[MAXN];

int Find(int i)
{
  return parent[i] = (parent[i] == i) ? i : Find(parent[i]);
}
void Union(int x, int y)
{
  int xx = Find(x), yy = Find(y);
  if (xx != yy)
  {
    if (sz[xx] > sz[yy])
      swap(xx, yy);
    parent[xx] = yy;
    sz[yy] += sz[xx];
    minn[yy] = min(minn[xx], minn[yy]);
    maxx[yy] = max(maxx[xx], maxx[yy]);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++)
  {
    parent[i] = i;
    sz[i] = 1;
    maxx[i] = i;
    minn[i] = i;
  }
  while (q--)
  {
    string t;
    cin >> t;
    if (t == "union")
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      Union(a, b);
    }
    else
    {
      int a;
      cin >> a;
      a--;
      cout << minn[Find(a)] + 1 << " " << maxx[Find(a)] + 1 << " " << sz[Find(a)] << endl;
    }
  }
}
