// busca ternaria
// divide em 3 partes, 2 mids
// mid1 = l + (r-l)/3
// mid2 = r - (r-l)/3
#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXL 100001

int n, key;
vector<int> ar;

int ts()
{
  int l = 0, r = n - 1;
  while (r >= l)
  {
    int mid1 = l + (r - l) / 3;
    int mid2 = r - (r - l) / 3;
    if (ar[mid1] == key)
      return mid1;
    if (ar[mid2] == key)
      return mid2;
    if (key < ar[mid1])
      r = mid1 - 1;
    else if (key > ar[mid2])
      l = mid2 + 1;
    else
    {
      l = mid1 + 1;
      r = mid2 - 1;
    }
  }
  return -1; // nao encontrado
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  ar.resize(n);
  for (int i = 0; i < n; i++)
    cin >> ar[i];
  sort(ar.begin(), ar.end());
  cin >> key;
  cout << ts() << endl;
  return 0;
}
