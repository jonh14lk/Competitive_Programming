# Editorial Maratona de Programação SECOMP 2022

## Dividindo Chocolate
### Autor: João Victor Ayalla

<details>
<summary>Editorial</summary>

A maior quantidade de pedaços de chocolate ele pode dar para cada amigo é N / M arredondado para baixo.
  
Complexidade: O(1)
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  int ans = n / m;
  cout << ans << endl;
  return 0;
}
```

</details>

## Linear Recurrence Problem
### Autor: João Victor Ayalla

<details>

<summary>Editorial</summary>

Um jeito de resolver o problema é fazendo recursivamente. Como N é no máximo 10, é suficiente para passar.
  
Complexidade: O(4^N)
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int a, b, c, d;

int f(int i)
{
  if (i == 0)
    return a;
  if (i == 1)
    return b;
  if (i == 2)
    return c;
  if (i == 3)
    return d;
  return (9 * f(i - 1)) + (2 * f(i - 2)) - (5 * f(i - 3)) + f(i - 4);
}
int main()
{
  int n;
  cin >> a >> b >> c >> d >> n;
  cout << f(n) << endl;
  return 0;
}
```

</details>

## Passagem da sorte
### Autor: João Victor Ayalla

<details>

<summary>Editorial</summary>

Um jeito de resolver o problema é lendo o número como string e em seguida checando as condições do problema
  
Complexidade: O(1)
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  string s;
  cin >> s;
  int a = 0, b = 0;
  for (int i = 0; i <=2; i++)
  {
    a += (s[i] - '0');
  }
  for (int i = 3; i <= 5; i++)
  {
    b += (s[i] - '0');
  }
  if (a % 7 == 0 && b % 2 == 0)
    cout << "YES\n";
  else 
    cout << "NO\n";
  return 0;
}
```

</details>


## Mensagem alienígena
### Autor: Nelson Gomes Neto

<details>

<summary>Editorial</summary>

Um detalhe interessante é que em linguagens como o C e o C++ por exemplo, nós podemos atribuir um inteiro a um char, e esse char vai passar a ter o caractere equivalente de acordo com a tabela ASCII. Sendo assim, podemos achar o mapeamento.
  
Complexidade: O(N)
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, x, y;
  cin >> n >> x >> y;
  while (n--)
  {
    int v;
    cin >> v;
    char c = (v * x + y) % 127;
    cout << c;
  }
  cout << endl;
  return 0;
}
```

</details>

## Simplesmente Café
### Autor: João Victor Ayalla

<details>

<summary>Editorial</summary>

A grande sacada aqui é olhar para os casos em que a soma de dois números pode ser ímpar:

- Par + Par = Par
- Par + Ímpar = Ímpar
- Ímpar + Ímpar = Par

Então, precisamos contar os pares (i, j) no qual A[i] é par e A[j] é ímpar, ou A[i] é ímpar e A[j] é par. Seja cnt_impar a quantidade de números ímpares no array e seja cnt_par a quantidade de números pares no array. A nossa resposta então vai ser igual a (cnt_impar * cnt_par), pois cada par (i, j) vai ser contado apenas uma vez, além disso, um número par fecha um par válido com todos os números impares e vice-versa.
  
Complexidade: O(N)
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> cnt(2, 0);
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    cnt[x % 2]++;
  }
  long long int ans = cnt[0] * 1ll * cnt[1];
  cout << ans << endl;
  return 0;
}
```

</details>

## O Protagonistinha e o seu robô
### Autor: João Victor Ayalla

<details>

<summary>Editorial</summary>

Para construir uma subsequência válida, podemos pensar nos seguintes casos:

- Se A < 0, então preciso de pelo menos abs(A) movimentos para cima
- se A > 0, então preciso de pelo menos abs(A) movimentos para baixo
- Se A = 0, então não preciso realizar nenhum movimento nem pra cima nem pra baixo
- Se B < 0, então preciso de pelo menos abs(B) movimentos para esquerda
- se B > 0, então preciso de pelo menos abs(B) movimentos para direita
- Se B = 0, então não preciso realizar nenhum movimento nem pra esquerda nem pra direita

No qual abs(X) é o valor absoluto de X.
  
Complexidade: O(N * log(N)) na implementação abaixo, mas da para ser feito em O(N).

</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  string s;
  cin >> s;
  int x, y;
  cin >> x >> y;
  map<char, int> cnt;
  for (int i = 0; i < n; i++)
  {
    cnt[s[i]]++;
  }
  bool ok = true;
  if (y > 0 && cnt['R'] < y)
    ok = false;
  if (y < 0 && cnt['L'] < -y)
    ok = false;
  if (x > 0 && cnt['D'] < x)
    ok = false;
  if (x < 0 && cnt['U'] < -x)
    ok = false;
  (ok) ? cout << "YES\n" : cout << "NO\n";
  return 0;
}
```

</details>


## Pai do avô do pai
### Autor: Nelson Gomes Neto

<details>

<summary>Editorial</summary>

Vamos ler o array de pais, e para responder uma pergunta vamos indo de pai em pai durante k vezes. Devemos tomar cuidado com o caso do -1 também. Lembrando que o nó 0 da árvore não tem pai.
 
Complexidade: O(N + (Q * K))
</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<int> p(n);
  p[0] = -1;
  for (int i = 1; i < n; i++)
  {
    cin >> p[i];
  }
  int q;
  cin >> q;
  while (q--)
  {
    int u, k;
    cin >> u >> k;
    while (k--)
    {
      u = p[u];
      if (u == -1)
        break;
    }
    cout << u << endl;
  }
  return 0;
}
```

</details>

## Aventura em Aracaju
### Autor: Pedro Victor Ferreira

<details>

<summary>Editorial</summary>

Vamos resolver o seguinte subproblema: Dado um número X, é possível fazer com que todos os copos tenham exatamente X ml de bebida?

A solução desse subproblema é a seguinte: Seja sum1 a soma dos (a[i] - X), para os a[i] > X. E seja sum2 a soma dos (X - a[i]), para os a[i] < X. Com isso, vai ser possível fazer com que todos os copos tenham exatamente X ml de bebida se:

![](https://drive.google.com/uc?export=view&id=1sBD-B868fN2BkfYBMClgLl7AFfRmeKyD)

Além disso, a gente pode perceber que se podemos encher todos os copos com X ml, também podemos encher todos os copos com Y ml (Y <= X).

Portanto, podemos fazer uma busca binária para achar o maior X possível no qual é possível fazer com que todos os copos tenham exatamente X ml de bebida.

Complexidade: O(N * log(1000))

</details>

<details>
<summary>Código (C++)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

#define eps 1e-6

int n, k;
int a[100005];

bool can(double x) 
{
    double sum1 = 0, sum2 = 0;
    for(int i = 0; i < n; i++) 
    {
        if(a[i] > x) 
          sum1 += (a[i] - x);
        else 
          sum2 += (x - a[i]);
    }
    double calc = sum1 - ((sum1 * k) / 100);
    return calc >= sum2;
}
int main()
{
  cin >> n >> k;
  for (int i = 0; i < n; i++)
  {
      cin >> a[i];
  }
  double l = 0, r = 1005;
  while (r - l > eps)
  {
    double mid = (l + r) / 2.0;
    if (can(mid))
      l = mid;
    else
      r = mid;
  }
  cout << fixed << setprecision(3) << l << endl;
  return 0;
}
```

</details>
