#include <stdio.h>

void percorrer_toda(int n, int matriz[][n], int contados[])
{
  int i, j, k;
  for (i = 0; i < n; i++)
  {
    for (k = 0; k < n; k++)
    {
      contados[k] = 0;
    }
    for (j = 0; j < n; j++)
    {
      contados[matriz[i][j] - 1] += 1;
    }
    for (k = 0; k < n; k++)
    {
      if (contados[k] > 1)
      {
        printf("NO\n");
        return;
      }
    }
  }
  for (j = 0; j < 9; j++)
  {
    for (k = 0; k < n; k++)
    {
      contados[k] = 0;
    }
    for (i = 0; i < n; i++)
    {
      contados[matriz[i][j] - 1] += 1;
    }
    for (k = 0; k < n; k++)
    {
      if (contados[k] != 1)
      {
        printf("NO\n");
        return;
      }
    }
    for (k = 0; k < n; k++)
    {
      contados[k] = 0;
    }
  }
  printf("YES\n");
  return;
}
void ler_matriz(int n, int contados[])
{
  int i, j;
  int matriz[n][n];
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      scanf("%d", &matriz[i][j]);
    }
  }
  percorrer_toda(n, matriz, contados);
}
void loop(int n, int i, int contados[])
{
  if (i == 1)
    return;
  else
  {
    ler_matriz(n, contados);
    printf("\n");
    loop(n, i + 1, contados);
  }
}
int main()
{
  int n, i;
  int contados[n];
  for (i = 0; i < n; i++)
    contados[i] = 0;
  scanf("%d", &n);
  loop(n, 0, contados);
  return 0;
}