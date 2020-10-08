#include <bits/stdc++.h>
using namespace std;

#define DEBUG(X) if (X)
#define pb push_back
typedef long long int lli;
typedef vector<lli> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<vector<ii>> vvii;
const int maxN = 2e3;

lli pd[maxN][maxN];

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  lli n, m;
  vi arr;
  cin >> n >> m;
  arr.resize(maxN);

  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n + 1; j++)
    {
      pd[i][j + 1] = (pd[i][j] + ((arr[j] % m) == i));
    }
  }

  lli q;
  cin >> q;

  while (q--)
  {
    int l, r, d, sum = 0;
    cin >> l >> r >> d;
    l--;
    cout << (pd[d][r] - pd[d][l]) << endl;
  }

  return 0;
}