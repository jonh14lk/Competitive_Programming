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
#define MAXN 2000011

signed main()
{
  int q;
  cin >> q;
  for (int c = 1; c <= q; c++)
  {
    int n;
    cin >> n;
    int matrix[n][n];
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        cin >> matrix[i][j];
      }
    }
    int sum = 0, ansc = 0, ansl = 0;
    for (int i = 0; i < n; i++)
    {
      sum += matrix[i][i];
    }
    for (int i = 0; i < n; i++)
    {
      set<int> at;
      for (int j = 0; j < n; j++)
      {
        at.insert(matrix[i][j]);
      }
      if (at.size() != n)
      {
        ansl++;
      }
    }
    for (int i = 0; i < n; i++)
    {
      set<int> at;
      for (int j = 0; j < n; j++)
      {
        at.insert(matrix[j][i]);
      }
      if (at.size() != n)
      {
        ansc++;
      }
    }
    cout << "Case #" << c << ": ";
    cout << sum << " " << ansl << " " << ansc << endl;
  }
  return 0;
}