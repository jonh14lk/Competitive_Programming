#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
 
  int q;
  cin >> q;
 
  while (q--)
  {
    int n, m, a;
    cin >> n;
    int princess[n];
    int kings[n];
 
    memset(princess, 0, sizeof(princess));
    memset(kings, 0, sizeof(kings));
 
    for (int i = 0; i < n; i++)
    {
      cin >> m;
      bool mar = false;
      for (int j = 0; j < m; j++)
      {
        cin >> a;
        a--;
 
        if (kings[a] == 0 && !mar)
        {
          kings[a] = 1;
          princess[i] = 1;
          mar = true;
        }
      }
    }
 
    int indexp = 0;
    int indexk = 0;
 
    for (int i = 0; i < n; i++)
    {
      if (princess[i] == 0)
      {
        indexp = i + 1;
      }
      if (kings[i] == 0)
      {
        indexk = i + 1;
      }
    }
 
    if (indexp != 0 && indexk != 0)
    {
      cout << "IMPROVE\n";
      cout << indexp << " " << indexk << endl;
    }
    else
    {
      cout << "OPTIMAL\n";
    }
  }
  return 0;
}
