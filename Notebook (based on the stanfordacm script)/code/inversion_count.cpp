// seja S = a1, a2 , ... , an
// uma inversao S e um par (i,j) com i < j e ai > aj

// Solucao O(n2) nao ideal:
//for(int i=0;i<n;i++)
//	for(int j=i+1;j<n;j++)
//		if(v[i]>v[j]) ans++;

// Em vez de trabalharmos com o vetor inteiro(n2), vamos dividir o vetor ao meio e trabalhar com suas metades,
// que chamaremos de u1 e u2.

// Queremos saber o valor de inv, o numero de inversoes em v. Ha tres tipos de inversoes (i,j)(i,j) em v:
// aquelas em que i e j estao ambos em u1, aquelas em que i e j estao ambos em u2 e aquelas
// em que i esta em u1 e j esta em u2.
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
#define MAXN 100001
#define INF 1000000000

int merge_sort(vector<int> &v)
{
  int ans = 0;

  if (v.size() == 1)
  {
    return 0;
  }

  vector<int> u1, u2;

  for (int i = 0; i < v.size() / 2; i++)
  {
    u1.pb(v[i]);
  }
  for (int i = v.size() / 2; i < v.size(); i++)
  {
    u2.pb(v[i]);
  }

  ans += merge_sort(u1);
  ans += merge_sort(u2);

  u1.pb(INF);
  u2.pb(INF);

  int ini1 = 0, ini2 = 0;

  for (int i = 0; i < v.size(); i++)
  {
    if (u1[ini1] <= u2[ini2])
    {
      v[i] = u1[ini1];
      ini1++;
    }
    else
    {
      v[i] = u2[ini2];
      ini2++;
      ans += u1.size() - ini1 - 1;
    }
  }

  return ans;
}
signed main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  cout << merge_sort(v) << endl;
  return 0;
}
