#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 100001
#define mod 1000000007
#define cd complex<double> // numeros complexos na STL

void dft(vector<cd> &a)
{
  int n = a.size();
  if (n == 1)
    return;
  vector<cd> a0(n / 2), a1(n / 2);
  for (int i = 0; 2 * i < n; i++)
  {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }
  dft(a0);
  dft(a1);
  double ang = 2 * PI / n;
  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; i++)
  {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    w *= wn;
  }
}
void inverse_dft(vector<cd> &a)
{
  int n = a.size();
  if (n == 1)
    return;
  vector<cd> a0(n / 2), a1(n / 2);
  for (int i = 0; 2 * i < n; i++)
  {
    a0[i] = a[2 * i];
    a1[i] = a[2 * i + 1];
  }
  inverse_dft(a0);
  inverse_dft(a1);
  double ang = 2 * PI / n * -1;
  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < n; i++)
  {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    a[i] /= 2;
    a[i + n / 2] /= 2;
    w *= wn;
  }
}
vector<int> fft(vector<int> a, vector<int> b)
{
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  fa.resize(n);
  fb.resize(n);
  dft(fa);                    // DFT(A)
  dft(fb);                    // DFT(B)
  for (int i = 0; i < n; i++) // DFT(A * B) = DFT(A) * DFT(B)
    fa[i] *= fb[i];
  inverse_dft(fa); // inverseDFT(DFT(A * B))
  vector<int> ans(n);
  for (int i = 0; i < n; i++)
    ans[i] = round(fa[i].real()); // arredondar para ter os coeficientes como inteiros
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, caso = 1;
  while (cin >> n >> m)
  {
    cout << "Caso #" << caso << ": ";
    vector<int> a(n + 1);
    vector<int> b(m + 1);
    for (int i = 0; i <= n; i++)
      cin >> a[i];
    for (int i = 0; i <= m; i++)
      cin >> b[i];
    vector<int> ans = fft(a, b);
    for (int i = 0; i <= n + m; i++)
    {
      cout << ans[i];
      (i == n + m) ? cout << endl : cout << " ";
    }
    caso++;
  }
  return 0;
}
// fft
// multiplicar dois polinomios A e B
// basic approach:
// aplicar a propiedade distributiva e fazer essa multiplicação em O(N^2)
// porém podemos melhorar
// vamos la
// 1  - todo polinomio de grau d que é representado na forma de coeficientes
//      de coeficientes possui uma representação em forma de d - 1 pontos
// 2  - para esse conjunto de pontos, só existe um único polinomio equivalente
// 3  - DFT -> transformação da representação de coeficientes para represntação
//             de pontos
// 4  - com isso, para multiplicar os dois polinomios agora basta multiplicar
//      os conjuntos de pontos e com isso obtemos a representação usando pontos
//      do polinomio resultante
// 5  - DFT(A * B) = DFT(A) * DFT(B);
// 6  - porém agora precisamos transformar a resposta obtida na multiplicação dos pontos
//      para a representação em que usa os coeficientes
// 7  - inverseDFT -> transformação da representação de pontos para represntação
//                    de coeficientes
// 8  - A * B = inverseDFT(DFT(A) * DFT(B))
// 9  - FFT -> metodo para computar a DFT em O(N * low(N))
// 10 - iremos usar divide and conquer para isso, vamos splitar o polinomio
//      atual em 2 polinomos de grau ((n / 2) - 1) , tal que, a soma deles
//      resulte no polinomio que tinhamos antes
// 11 - agora para achar a inverseDFT de uma DFT, iremos escrever a DFT
//      em forma de matriz, essa matriz é chamada de matriz de vandermonde
//      e em geral, podemos escrever a resposta como uma multiplicação de
//      matrizes
// 12 - essa multplicação de matrizes pode ser descrita como:
//      a^-1 * b = c
//      no qual:
//      a^-1 -> inversa da matriz a(DFT)
//      b -> valores dos coeficientes do polinomio A
//      c -> valores dos coeficientes da resposta
