#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100001
#define mod 998244353

namespace sa
{
  struct state
  {
    int len, suf_link;
    map<char, int> nxt;
  };
  
  vector<int> term;
  state st[2 * MAXN];
  int dp[2 * MAXN];
  int sz, last;

  void init()
  {
    memset(dp, -1, sizeof(dp));
    st[0].len = 0;
    st[0].suf_link = -1;
    sz++;
    last = 0;
  }
  void get_link(int curr, int p, char c)
  {
    while (p != -1 && !st[p].nxt.count(c))
    {
      st[p].nxt[c] = curr;
      p = st[p].suf_link;
    }
    if (p == -1)
    {
      st[curr].suf_link = 0;
      return;
    }
    int q = st[p].nxt[c];
    if (st[p].len + 1 == st[q].len)
    {
      st[curr].suf_link = q;
      return;
    }
    int clone = sz;
    sz++;
    st[clone].len = st[p].len + 1;
    st[clone].nxt = st[q].nxt;
    st[clone].suf_link = st[q].suf_link;
    while (p != -1 && st[p].nxt[c] == q)
    {
      st[p].nxt[c] = clone;
      p = st[p].suf_link;
    }
    st[q].suf_link = clone;
    st[curr].suf_link = clone;
  }
  void build(string &s)
  {
    for (auto const &c : s)
    {
      int curr = sz;
      sz++;
      st[curr].len = st[last].len + 1;
      get_link(curr, last, c);
      last = curr;
    }
    // achar os estados terminais
    // um estado terminal é aquele que representa um sufixo da string s
    int p = last;
    while (p != -1)
    {
      term.pb(p);
      p = st[p].suf_link;
    }
  }
  void dfs2(int v)
  {
    if (dp[v] != -1)
      return;
    dp[v] = 1;
    for (auto const &u : st[v].nxt)
    {
      if (!u.sec)
        continue;
      dfs2(u.sec);
      dp[v] += dp[u.sec];
    }
  }
  void dfs(int v, int k, int &at, string &curr)
  {
    if (at == k)
      return;
    for (auto const &u : st[v].nxt)
    {
      if (!u.sec)
        continue;
      if (at + dp[u.sec] < k)
      {
        at += dp[u.sec];
        continue;
      }
      curr.pb(u.fir);
      at++;
      dfs(u.sec, k, at, curr);
      if (at == k)
        return;
      curr.pop_back();
    }
  }
  void find_kth(int k)
  {
    int at = 0;
    string curr = "";
    dfs(0, k, at, curr);
    cout << curr << endl;
  }
} // namespace sa
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  sa::init();
  sa::build(s);
  sa::dfs2(0);
  int q;
  cin >> q;
  while (q--)
  {
    int k;
    cin >> k;
    sa::find_kth(k);
  }
  return 0;
}
// https://cp-algorithms.com/string/suffix-automaton.html
// suffix automaton
// definição: um suffix automaton de uma string s é um automato finito deterministico
// que aceita todos os suffixos da string s.
// ou seja:
// um suffix automaton eh um grafo aciclico orientado
// tal que, um vértice representa um estado
// e uma aresta representa uma transição (um caractere a mais em relação ao estado(suffixo) atual)
// t0 -> estado inicial(string vazia), e todos os demais estados podem ser alcançados a partir de t0
// o suffix automaton minimiza o numero de vertices

// a propiedade mais importante de um suffix automaton eh a de que
// ele contem informações sobre todas as substrings de s
// pois, qualquer caminho começando do estado t0 corresponde a uma substring de s

// conceitos:

// 1 - endpos
// seja t uma substring de s, endpos(t) eh o conjunto de todas os indices(posições)
// na string s no qual todas as ocorrencias de t acabam
// por exemplo, se s = "abcbc" e t = "bc"
// logo endpos(t) = {2, 4}
// com isso se duas duas substrings t1 e t2 possuem os seus endpos iguais,
// chamamos de endpos-equivalent e dai podemos extrair algumas informações
// info 1: se duas substrings u e w u.size() <= w.size(), se u eh um sufixo de w, logo endpos(u) está contido em endpos(w)
// info 2: se duas substrings u e w u.size() <= w.size(), se u nao eh um sufixo de w, logo nao existe intersecção entre endpos(u) e endpos(w)

// 2 - suffix link
// seja v algum estado != t0,  sabemos que v corresponde a classe de strings que possui os mesmos endpos
// seja w a maior dessas strings, com isso, todas as demais sao suffixos de w
// com isso um suffix_link(v) corresponde ao maior suffix de w que está em outra classe de equivalencia pelos endpos
// com isso podemos abstrair algumas informações:
// info 1: os suffix links foram uma arvore enraizada em t0
// info 2: se construirmos uma arvore usando os sets endpos, a estrutura sera a arvore com os suffix links

// com isso, vamos ao algoritimo
// 1 - vai ser online, e iremos adicionar os caracteres de 1 por 1, da esquerda para a direita
// 2 - com isso para adicionar um novo char, seja v o ultimo estado que adicionamos antes do atual, adicionamos uma aresta
// do proximo em relaçao a ele e iremos procurar pelo suffix link para adicionar
// 3 - complexidade O(n) ou O(n log k), se usarmos uma map para guardar as transições partindo de um estado

// exemplos de aplicações:

// 1 - checar se t aparece em s como substring:
// construa o suffix automaton de s, e vamos tentar fazer um caminho partindo de t0
// se em algum momento, nao existir transição, logo não existe
// se conseguir chegar no final, existe

// 2 - numero de substrings diferentes de s
// constura o suffix automaton de s, sabemos que, cada substring de s corresponde a um caminho no automato
// com isso, o numero de substrings distintas eh o numero de caminhos diferentes que começam de t0
// e terminam em algum canto
// isso pode ser calculado facilmente com uma dpzinha

// 3 - tamanho total de todas as substrings distintas de s
// similar a solução passada, podemos fazer isso com uma dpzinha :)

// 4 - a k-esima menor substring lexicografica
// a k-esima menor substring lexicograficamente corresponde ao k-esimo path no suffix automaton
// se considerarmos as transições sempre indo do menor char para o maior durante o percurso

// 5 - o menor cyclic shift
// construa o suffix automaton da string s + s (duplicada)
// com isso o suffix automaton vai conter todos os cyclic shifts da string s
// e agora o problema eh reduzido para: encontre o menor caminho lexicograficamente de tamanho s.size()

// 6 - numero de ocorrencias de uma substring t em s
// construa o suffix automaton da string s
// com isso, quando criamos um no que nao seja o t0 nem um clone
// inicializamos cnt[v] = 1
// depois vamos percorrer todo os estados em ordem decrescente de len
// e aplicando cnt[link(v)] += cnt[v]
// no final, para responder a query basta fazer o caminho ate o estado que quisermos e printar o cnt dele

// e mais uma porrada de aplicações além dessas :)

// example of a problem: https://www.spoj.com/problems/SUBLEX/
// ver qual a k-th string lexicografica sem repetição
// note que o k pode ser gigante
// ideia: calcular dp[v] -> quantidade de caminhos que começam em v
// dai para cada query roda um dfs, sendo que, so vou pro proximo estado se at + dp[u] >= k
// caso contrário, posso ignorar
