#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int x;
  cin >> x;
  if (x == 1)
  {
    cout << 1 << endl;
    return 0;
  }
  int msb;
  for (int b = 60; b >= 0; b--)
  {
    if (x & (1ll << b))
    {
      msb = b;
      break;
    }
  }
  if ((1ll << msb) == x)
  {
    cout << x - 1 << endl;
    return 0;
  }
  int y = 0, l = msb, r = 0;
  while (l >= r)
  {
    int new_y = y | (1ll << l) | (1ll << r);
    if (new_y <= x)
    {
      y = new_y;
    }
    l--;
    r++;
  }
  cout << y << endl;
  return 0;
}
// para x = 1 a resposta eh 1
// para potencias de dois, a resposta eh x - 1
// caso contrario, o msb de x e y vai ser o mesmo, entao podemos aplicar a ideia greedy, que eh:
// o msb de x e y vao ser o mesmo, entao podemos ir considerando do maior bit pro menor bit, e vendo se podemos setar
// mas se tiver que setar um bit na posicao k, teremos que setar o bit na posicao msb - k tambem