# Maratona de Programação SECOMP 2025

Para auxiliar no entendimento das soluções descritas aqui, acima há um código de solução exemplo em C++ para cada questão.



## A - Estimando os Balões da Maratona

É possível ler os números da entrada como inteiros e, em linguagens como C/C++, o operador de divisão entre inteiros já realiza a divisão arredondando para baixo.  
Assim, basta escrever a expressão dada no enunciado e resolver o problema diretamente.



## B - Construindo um estacionamento

Uma boa estratégia para resolver problemas **construtivos** é começar elaborando uma solução para casos mais simples e, a partir disso, adaptar a construção para cenários mais gerais.  
Testar essas construções no papel, com casos pequenos, pode ser uma ótima.

Neste caso, quando o número de colunas é igual a `5` (`M = 5`), podemos fazer algo como:

**Exemplo para N = 3, M = 5:**

| 1 | 1 | 0 | 2 | 2 |
|---|---|---|---|---|
| 3 | 3 | 0 | 4 | 4 |
| 5 | 5 | 0 | 6 | 6 |

Essa é uma forma válida de construção, onde **80% das posições são vagas**, formando uma configuração aceitável.

De forma análoga, podemos replicar esse padrão quando `M` é múltiplo de 5.

**Exemplo para N = 3, M = 15:**

| 1 | 1 | 0 | 2 | 2 | 7 | 7 | 0 | 8 | 8 | 13 | 13 | 0 | 14 | 14 |
|---|---|---|---|---|---|---|---|---|---|----|----|---|----|----|
| 3 | 3 | 0 | 4 | 4 | 9 | 9 | 0 | 10 | 10 | 15 | 15 | 0 | 16 | 16 |
| 5 | 5 | 0 | 6 | 6 | 11 | 11 | 0 | 12 | 12 | 17 | 17 | 0 | 18 | 18 |

Assim, temos uma construção para os casos em que `M` é múltiplo de 5.  
Para os demais valores, precisamos tratar os possíveis **restos da divisão de `M` por 5**.

### (M % 5) == 1

Podemos preencher a última coluna da matriz com vagas verticais.  

**Exemplo para N = 4, M = 6:**

| 1 | 1 | 0 | 2 | 2 | 9 |
|---|---|---|---|---|---|
| 3 | 3 | 0 | 4 | 4 | 9 |
| 5 | 5 | 0 | 6 | 6 | 10 |
| 7 | 7 | 0 | 8 | 8 | 10 |

**Exemplo para N = 5, M = 6**  
(Aqui sobra um zero no final, mas ainda satisfaz o mínimo de 80%.)

| 1 | 1 | 0 | 2 | 2 | 11 |
|---|---|---|---|---|----|
| 3 | 3 | 0 | 4 | 4 | 11 |
| 5 | 5 | 0 | 6 | 6 | 12 |
| 7 | 7 | 0 | 8 | 8 | 12 |
| 9 | 9 | 0 | 10 | 10 | 0 |

**Caso especial:** para `N = 3, M = 6`, foi necessário um tratamento especial no código.

| 7 | 7 | 8 | 8 | 9 | 9 |
|---|---|---|---|---|---|
| 1 | 2 | 3 | 4 | 5 | 6 |
| 1 | 2 | 3 | 4 | 5 | 6 |

### (M % 5) == 2

Podemos construir algo como:

| 1 | 1 | 0 | 2 | 2 | 7 | 7 |
|---|---|---|---|---|---|---|
| 3 | 3 | 0 | 4 | 4 | 8 | 8 |
| 5 | 5 | 0 | 6 | 6 | 9 | 9 |

Ou seja, colocamos vagas **horizontais** nas duas últimas colunas de cada linha.

### (M % 5) == 3

Podemos preencher as duas **primeiras colunas** de cada linha com vagas horizontais e, em seguida, aplicar a ideia do caso de resto 1 (preenchendo a **última coluna** com vagas verticais).

**Exemplo para N = 3, M = 3:**

| 1 | 1 | 4 |
|---|---|---|
| 2 | 2 | 4 |
| 3 | 3 | 0 |

**Exemplo para N = 3, M = 8:**

| 1 | 1 | 4 | 4 | 0 | 5 | 5 | 10 |
|---|---|---|---|---|---|---|----|
| 2 | 2 | 6 | 6 | 0 | 7 | 7 | 10 |
| 3 | 3 | 8 | 8 | 0 | 9 | 9 | 0 |

### (M % 5) == 4

Nesse caso, basta colocar vagas **horizontais** nas duas últimas colunas de cada linha, e também nas **duas primeiras colunas** de cada linha.

**Exemplo para N = 3, M = 9:**

| 1 | 1 | 4 | 4 | 0 | 5 | 5 | 10 | 10 |
|---|---|---|---|---|---|---|----|----|
| 2 | 2 | 6 | 6 | 0 | 7 | 7 | 11 | 11 |
| 3 | 3 | 8 | 8 | 0 | 9 | 9 | 12 | 12 |


## C - Distribuindo doces

Em certos problemas, é mais fácil identificar quando **é impossível** do que quando **é possível**.  
Neste caso, a resposta será **"NÃO"** se:

- `K < (N * L)`, pois alguém ficaria com menos do que `L` doces; ou  
- `K > (N * R)`, pois alguém ficaria com mais do que `R` doces.



## D - Ordenando itens

Como a maioria dos problemas **construtivos**, existem diversas soluções possíveis para este problema, mas aqui vou descrever a ideia que utilizei.

### 1. Separação em vetores auxiliares

Podemos separar os números do vetor de belezas da entrada `V` em **três vetores auxiliares**, de acordo com o valor `X`:

- **Vetor A:** números de `V` que são menores do que `X / 2`;
- **Vetor B:** números de `V` que são maiores do que `X / 2`;
- **Vetor C:** números de `V` que são iguais a `X / 2`.

Por exemplo, se `V = [2, 4, 3, 1, 7, 3]` e `X = 6`, então:

- `A = [2, 1]`
- `B = [4, 7]`
- `C = [3, 3]`

### 2. Construindo o vetor D

Vamos começar **juntando os números** dos vetores `A` e `B` em um novo vetor `D`.

Um fato importante é que **dois números adjacentes em `A`** e **dois números adjacentes em `B`** **nunca somam `X`**, pois:
- em `A`, ambos são menores do que `X / 2`;  
- em `B`, ambos são maiores do que `X / 2`.

Assim, podemos montar o vetor `D` da seguinte forma:

$$
D = [A_1, A_2, \dots, A_{|A|}, B_1, B_2, \dots, B_{|B|}]
$$

garantindo que:

$$
A_{|A|} + B_1 \neq X
$$

O **único caso** em que não conseguimos montar o vetor dessa forma é quando:
- todos os números em `A` são iguais entre si;
- todos os números em `B` são iguais entre si; e  
- qualquer par `(a, b)` com `a ∈ A` e `b ∈ B` satisfaz `a + b = X`.

Fora esse caso, **sempre é possível** encontrar uma ordenação que atenda à condição acima.

### 3. Caso em que X é ímpar

Se `X` for **ímpar**, o vetor `C` será **vazio**, já que `X / 2` não é um número inteiro.  
Nesse caso, basta verificar se foi possível construir o vetor `D` conforme o passo anterior.

### 4. Caso em que X é par

Se `X` for **par** e o vetor `C` **não for vazio**, precisamos inserir os elementos de `C` dentro do vetor `D` de maneira adequada.

#### a) Corrigindo o ponto de junção

Se o último elemento de `A` e o primeiro de `B` somam `X`:

$$
A_{|A|} + B_1 = X
$$

devemos **inserir uma ocorrência de `(X / 2)`** entre eles, de modo a "quebrar" o par problemático:

$$
D = [A_1, A_2, \dots, A_{|A|}, \tfrac{X}{2}, B_1, B_2, \dots, B_{|B|}]
$$

#### b) Distribuindo os demais elementos de C

Os outros elementos iguais a `(X / 2)` devem ser intercalados entre os elementos de `A` e `B`, da seguinte forma:

$$
D = [\tfrac{X}{2}, A_1, \tfrac{X}{2}, A_2, \dots, \tfrac{X}{2}, A_{|A|}, \tfrac{X}{2}, B_1, \tfrac{X}{2}, B_2, \dots, \tfrac{X}{2}, B_{|B|}, \tfrac{X}{2}]
$$

É importante garantir que **não sejam inseridas mais ocorrências de `(X / 2)`** do que as existentes no vetor `C`.

#### c) Verificando a impossibilidade

Se houver **mais elementos em `C` do que o número de "espaços" possíveis** para intercalar:

$$
|C| > |A| + |B| + 1
$$

então é **impossível** construir uma resposta válida, pois necessariamente haveria **duas ocorrências consecutivas de `(X / 2)`**.



## E - Bases palindrômicas

De certa forma, esse é um problema que pede uma implementação direta do enunciado.  
Podemos descrever o passo a passo do algoritmo como:

1. Percorrer todas as bases de 2 até 16;  
2. Converter o número dado para cada base;  
3. Armazenar essa representação em uma string ou vetor;  
4. Verificar se essa string/vetor é um palíndromo.



## F - Dominós na horizontal

Outro problema de implementação direta.  
Deve-se percorrer a matriz dada na entrada e, se existirem duas posições adjacentes na **mesma linha** cujo caractere seja `'N'` e **nenhum dominó ainda ocupe** essas posições, é possível colocar um dominó nelas.



## G - Prova de P1

Esse problema pode ser resolvido de várias maneiras, mas talvez a mais simples seja perceber que os números `1`, `2` e `4` são **potências de 2**.  
Assim, podemos analisar a **representação binária** dos números `M` e `A` e observar quais bits estão setados em um ou no outro número para compor a resposta.

Essa definição corresponde exatamente à operação de **bitwise OR**, portanto basta imprimir o valor de `(M | A)`.



## H - Essa questão é muito boa

*(Descrição ainda não adicionada.)*



## I - I de interativo

A grande sacada do problema está em perceber os seguintes fatos:

Se `A < B`, então:
- `(A % B) > (B % A)`
- `(A % B) = A`

Assim, podemos resolver o problema da seguinte forma:

1. Começamos com os índices `x = 1` e `y = 2`, e fazemos duas perguntas: `? x y` e `? y x`.  
2. Com base nas respostas, sabemos qual dos dois índices representa o menor número e qual o valor dele:  
   - Se a resposta da primeira pergunta for **maior** que a da segunda, então `resposta[x] = valor da pergunta 1`;  
   - Caso contrário, `resposta[y] = valor da pergunta 2`.  
3. Se descobrimos `resposta[x]`, atualizamos `x = 3` e seguimos o mesmo processo; caso contrário, atualizamos `y = 3`.  
4. Repetimos o processo até restar apenas um índice sem valor, e esse índice `i` terá `resposta[i] = N`.



## J - Persistência multiplicativa

Para resolver, basta implementar a operação de substituir o número `X` pelo **produto de seus dígitos** repetidamente, até restar um número de um único dígito.  
O número de iterações feitas é a resposta.  

A parte mais desafiadora é justamente calcular o produto dos dígitos de um número, mas é um ótimo exercício para o leitor.



## K - Quantas progressões aritméticas existem?

A grande sacada do problema está em **fixar a razão `D`** da progressão aritmética.  
Como o enunciado impõe a restrição `R - L ≤ 10⁵`, é viável percorrer todas as razões possíveis no intervalo `D ∈ [1, R - L]`.

### 1. Construindo os conjuntos de candidatos

Para cada valor de `D`, podemos gerar dois conjuntos de valores possíveis:

- **CL**: todos os números que podem aparecer **antes ou iguais a** um certo `A`, diminuindo de `D` em `D`, enquanto forem `≥ L`  
  → `CL = {A, A - D, A - 2D, A - 3D, ...}` até `≥ L`.

- **CR**: todos os números que podem aparecer **após ou iguais a** `A`, aumentando de `D` em `D`, enquanto forem `≤ R`  
  → `CR = {A, A + D, A + 2D, A + 3D, ...}` até `≤ R`.

Cada par `(CL[i], CR[j])` define uma possível progressão aritmética que começa em `CL[i]`, termina em `CR[j]` e tem razão `D`.


### 2. Verificando se a soma é igual a `S`

Sabemos que a soma de uma progressão aritmética é dada por:

$$
S = \frac{(a_1 + a_n) \times n}{2}
$$

onde:
- `a₁ = CL[i]`
- `aₙ = CR[j]`
- `n = ((aₙ - a₁) / D) + 1`

Logo, precisamos verificar se essa soma `S` é igual ao valor fornecido na entrada.

### 3. Como buscar os pares válidos

Existem duas abordagens principais para encontrar os pares `(CL[i], CR[j])` que satisfazem a soma desejada:

#### **Abordagem com Busca Binária**

1. Para cada `D` fixo, percorremos todos os elementos de `CL`.  
2. Para cada elemento `x = CL[i]`, queremos encontrar `y` em `CR` tal que, a soma da PA de `x` a `y` com razão `D` é igual a `S`.
3. Como `CR` está ordenado (pois é construída com passo fixo `D`), podemos aplicar **busca binária** para encontrar o valor `y` que satisfaz essa igualdade. Assim, vai existir **no máximo um** valor `y` que satisfaz a igualdade, e caso satisfaça, podemos incrementar a resposta em 1.

Essa abordagem é eficiente porque cada busca leva `O(log |CR|)`, e `|CR|` é proporcional a `(R - L) / D`.

#### **Abordagem com Dois Ponteiros (Two Pointers)**

Outra forma de resolver é usando **dois ponteiros**, consierando as listas `CL` e `CR` ordenadas em ordem crescente.

1. Inicializamos dois ponteiros:
   - `i = 0` (para percorrer `CL`)
   - `j = 0` (para percorrer `CR`)
2. Calculamos a soma `S(i, j)` da progressão que começa em `CL[i]` e termina em `CR[j]`.
3. Se `S(i, j) < S`, precisamos aumentar a soma — logo, incrementamos `j` (andando para a direita em `CR`).
4. Se `S(i, j) > S`, a soma está muito grande — então incrementamos `i` (andando em `CL`).
5. Se `S(i, j) = S`, encontramos uma progressão válida, podemos incrementar a resposta em 1 e incrementar `i` e `j`.

Essa abordagem percorre as listas de forma linear (`O(|CL| + |CR|)`).


### 4. Conclusão

Assim, o algoritmo geral é:

1. Percorrer todas as razões `D ∈ [1, R - L]`;
2. Construir `CL` e `CR`;
3. Usar **busca binária** ou **dois ponteiros** para encontrar os pares `(CL[i], CR[j])` cuja soma da PA seja igual a `S`.


## L - Aprendendo alemão

Como a letra `S` pode aparecer no máximo três vezes na string, podemos resolver o problema considerando os seguintes casos:

1. Se houver **0 ou 1 ocorrência** de `S`, só existe uma maneira de escrever a string, pois não há substituições possíveis.  
2. Se houver **2 ocorrências** de `S` e elas forem **adjacentes**, é possível substituí-las por **`ß`**; caso contrário, só há uma forma de escrever a string.  
3. Se houver **3 ocorrências** de `S` e elas forem **adjacentes**, podemos escrever `"SSS"` como `"Sß"` ou `"ßS"`.  
   Caso não sejam todas adjacentes, basta verificar se existe **algum par de `S` consecutivos** que possa ser substituído por **`ß`**; se não houver, só existe uma maneira de escrever a string.
