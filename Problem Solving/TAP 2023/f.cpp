#include <bits/stdc++.h>
using namespace std;
#define int long long
double dist(double x1, double y1, double x2, double y2)
{
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int w, l, tx, ty;
  cin >> w >> l >> tx >> ty;
  vector<double> distA;
  vector<double> distR;
  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    double a = dist(x, y, tx, ty);
    distA.push_back(a);
    // cout<<a<<"\n";
  }

  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    double b = dist(x, y, tx, ty);
    distR.push_back(b);
    // cout<<b<<"\n";
  }

  sort(distA.begin(), distA.end());
  sort(distR.begin(), distR.end());

  int ans = 0;
  // cout<<distA[0]<<" "<<distR[0]<<"\n";
  if (distA[0] < distR[0])
  {
    cout << "A"
         << " ";
    for (int i = 0; i < n; i++)
    {
      if (distA[i] >= distR[0])
      {
        break;
      }
      ans++;
    }
  }
  else
  {
    cout << "R"
         << " ";
    for (int i = 0; i < n; i++)
    {
      if (distR[i] >= distA[0])
      {
        break;
      }
      ans++;
    }
  }

  cout << ans << "\n";
  return 0;
}
