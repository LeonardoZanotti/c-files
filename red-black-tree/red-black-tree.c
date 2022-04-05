#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0;

typedef struct arvoreRB
{
  int info;
  int cor;
  struct arvoreRB *esq;
  struct arvoreRB *dir;
} ArvoreRB;

int eh_no_vermelho(ArvoreRB *no)
{
  return no && no->cor == RED;
}

int buscar(ArvoreRB *a, int v)
{
  return a != NULL && (v < a->info ? buscar(a->esq, v) : (v > a->info ? buscar(a->dir, v) : 1));
}

void in_order(ArvoreRB *a)
{
  if (!a)
    return;
  in_order(a->esq);
  printf("%d ", a->info);
  in_order(a->dir);
}

void print(ArvoreRB *a, int spaces)
{
  int i;
  for (i = 0; i < spaces; i++)
    printf(" ");
  if (!a)
  {
    printf("//\n");
    return;
  }

  printf("%d\n", a->info);
  print(a->esq, spaces + 2);
  print(a->dir, spaces + 2);
}

int main()
{
  ArvoreRB *a;
}
