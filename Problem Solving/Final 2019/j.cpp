#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<double, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200001
#define mod 998244353

int n, q;
vector<int> v;

namespace seg
{
  int seg[4 * MAXN];

  void update(int i, int l, int r, int q, int x)
  {
    if (l == r)
    {
      seg[i] = x;
      return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
      update(i << 1, l, mid, q, x);
    else
      update((i << 1) | 1, mid + 1, r, q, x);
    seg[i] = max(seg[i << 1], seg[(i << 1) | 1]);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (l > r || l > qr || r < ql)
      return -1;
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return max(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
  int build(int l, int r, int i)
  {
    if (l == r)
      return seg[i] = v[l];
    int mid = (l + r) >> 1;
    return seg[i] = max(build(l, mid, i << 1), build(mid + 1, r, (i << 1) | 1));
  }
  void upd(int i, int x)
  {
    update(1, 0, n - 1, i, x);
  }
  int qry(int l, int r)
  {
    return query(0, n - 1, l, r, 1);
  }
  int qry2(int l, int r, int x)
  {
    int i = l;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      (qry(i, mid) > x) ? r = mid : l = mid + 1;
    }
    return (qry(i, l) > x) ? l : i;
  }
  int qry3(int l, int r, int x)
  {
    int i = r;
    while (l < r)
    {
      int mid = (l + r + 1) >> 1;
      (qry(mid, i) > x) ? l = mid : r = mid - 1;
    }
    return (qry(l, i) > x) ? l : i;
  }
}; // namespace seg
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  seg::build(0, n - 1, 1);
  while (q--)
  {
    char t;
    cin >> t;
    if (t == 'U')
    {
      int i, x;
      cin >> i >> x;
      i--;
      v[i] = x;
      seg::upd(i, x);
    }
    else if (t == 'L')
    {
      int i;
      cin >> i;
      i--;
      int a = seg::qry(0, i), b = seg::qry(i, n - 1);
      if (a <= v[i])
        cout << i + 1 << endl;
      else if (a > b)
        cout << seg::qry3(0, i - 1, b) + 1 << endl;
      else
        cout << seg::qry2(i + 1, n - 1, a) + 1 << endl;
    }
    else
    {
      int i;
      cin >> i;
      i--;
      int a = seg::qry(0, i), b = seg::qry(i, n - 1);
      if (b <= v[i])
        cout << i + 1 << endl;
      else if (a > b)
        cout << seg::qry3(0, i - 1, b) + 1 << endl;
      else
        cout << seg::qry2(i + 1, n - 1, a) + 1 << endl;
    }
  }
  return 0;
}
// para uma query u i, podemos ver:
// seja u a direção inicial da query
// caso nao exista ninguem maior do que v[i] nessa direção inicial
// a resposta vai ser o propio indice i
// Caso contrario
// podemos achar o maior valor nos intevalos [0, i] e [i, n - 1]
// vamos chamar esses valores de a e b
// caso a > b
// a resposta vai ser o primeiro valor a esquerda de i que seja maior do que b
// caso contrario
// a resposta vai ser o primeiro valor a direita de i que seja maior do que a

// podemos provar isso simplesmente porque, achando o maximo dos dois lados
// e saindo do menor desses maximos para a direção oposta
// nao tem como voltar para a outra direção apos o movimento feito
// pois ja passamos pelo maximo daquele lado
// logo a resposta vai ser aquele cara

// apos ter a sacada genial, fica simples
// uma segtree de maximo com busca binaria é suficiente
