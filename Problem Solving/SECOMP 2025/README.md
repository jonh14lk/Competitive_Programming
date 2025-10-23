# Maratona de Programação SECOMP 2025

Para auxiliar no entendimento das soluções descritas aqui, acima há um código de solução exemplo em C++ para cada questão.

---

## A - Estimando os Balões da Maratona

É possível ler os números da entrada como inteiros e, em linguagens como C/C++, o operador de divisão entre inteiros já realiza a divisão arredondando para baixo.  
Assim, basta escrever a expressão dada no enunciado e resolver o problema diretamente.

---

## B - Construindo um estacionamento

*(Descrição ainda não adicionada.)*

---

## C - Distribuindo doces

Em certos problemas, é mais fácil identificar quando **é impossível** do que quando **é possível**.  
Neste caso, a resposta será **"NÃO"** se:

- `K < (N * L)`, pois alguém ficaria com menos do que `L` doces; ou  
- `K > (N * R)`, pois alguém ficaria com mais do que `R` doces.

---

## D - Ordenando itens

*(Descrição ainda não adicionada.)*

---

## E - Bases palindrômicas

De certa forma, esse é um problema que pede uma implementação direta do enunciado.  
Podemos descrever o passo a passo do algoritmo como:

1. Percorrer todas as bases de 2 até 16;  
2. Converter o número dado para cada base;  
3. Armazenar essa representação em uma string ou vetor;  
4. Verificar se essa string/vetor é um palíndromo.

---

## F - Dominós na horizontal

Outro problema de implementação direta.  
Deve-se percorrer a matriz dada na entrada e, se existirem duas posições adjacentes na **mesma linha** cujo caractere seja `'N'` e **nenhum dominó ainda ocupe** essas posições, é possível colocar um dominó nelas.

---

## G - Prova de P1

Esse problema pode ser resolvido de várias maneiras, mas talvez a mais simples seja perceber que os números `1`, `2` e `4` são **potências de 2**.  
Assim, podemos analisar a **representação binária** dos números `M` e `A` e observar quais bits estão setados em um ou no outro número para compor a resposta.

Essa definição corresponde exatamente à operação de **bitwise OR**, portanto basta imprimir o valor de `(M | A)`.

---

## H - Essa questão é muito boa

*(Descrição ainda não adicionada.)*

---

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
4. Repetimos o processo até restar apenas um índice sem valor — esse índice `i` terá `resposta[i] = N`.

---

## J - Persistência multiplicativa

Para resolver, basta implementar a operação de substituir o número `X` pelo **produto de seus dígitos** repetidamente, até restar um número de um único dígito.  
O número de iterações feitas é a resposta.  

A parte mais desafiadora é justamente calcular o produto dos dígitos de um número, mas é um ótimo exercício para o leitor.

---

## K - Quantas progressões aritméticas existem?

A grande sacada do problema está em **fixar a razão `D`** da progressão aritmética.  
Como o enunciado impõe a restrição `R - L ≤ 10⁵`, é viável percorrer todas as razões possíveis no intervalo `D ∈ [1, R - L]`.

---

### 1. Construindo os conjuntos de candidatos

Para cada valor de `D`, podemos gerar dois conjuntos de valores possíveis:

- **CL**: todos os números que podem aparecer **antes ou iguais a** um certo `A`, diminuindo de `D` em `D`, enquanto forem `≥ L`  
  → `CL = {A, A - D, A - 2D, A - 3D, ...}` até `≥ L`.

- **CR**: todos os números que podem aparecer **após ou iguais a** `A`, aumentando de `D` em `D`, enquanto forem `≤ R`  
  → `CR = {A, A + D, A + 2D, A + 3D, ...}` até `≤ R`.

Cada par `(CL[i], CR[j])` define uma possível progressão aritmética que começa em `CL[i]`, termina em `CR[j]` e tem razão `D`.


### 2. Verificando se a soma é igual a `S`

Sabemos que a soma de uma progressão aritmética é dada por:

\[
S = \frac{(a_1 + a_n) \times n}{2}
\]

onde:
- `a₁ = CL[i]`
- `aₙ = CR[j]`
- `n = ((aₙ - a₁) / D) + 1`

Logo, precisamos verificar se essa soma `S` é igual ao valor fornecido na entrada.

### 3. Como buscar os pares válidos

Existem duas abordagens principais para encontrar os pares `(CL[i], CR[j])` que satisfazem a soma desejada:

#### **Abordagem com Busca Binária**

1. Para cada `D` fixo, percorremos todos os elementos de `CL`.  
2. Para cada elemento `x = CL[i]`, queremos encontrar `y` em `CR` tal que:

   \[
   \frac{(x + y) \times (((y - x) / D) + 1)}{2} = S
   \]

3. Como `CR` está ordenado (pois é construída com passo fixo `D`), podemos aplicar **busca binária** para encontrar o valor `y` que satisfaz essa igualdade. Assim, vai existir no máximo um valor `y` que satisfaz a igualdade, e caso satisfaça, podemos incrementar a resposta em 1.

Essa abordagem é eficiente porque cada busca leva `O(log |CR|)`, e `|CR|` é proporcional a `(R - L) / D`.

---

#### **Abordagem com Dois Ponteiros (Two Pointers)**

Outra forma de resolver é usando **dois ponteiros**, aproveitando que as listas `CL` e `CR` são ordenadas.

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

---

## L - Aprendendo alemão

*(Descrição ainda não adicionada.)*
