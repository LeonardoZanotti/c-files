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

void printTreeOrder(ArvoreRB *a)
{
  if (!a)
    return;
  printTreeOrder(a->esq);
  printf("%d ", a->info);
  printTreeOrder(a->dir);
}

void printTree(ArvoreRB *a, int spaces)
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
  printTree(a->esq, spaces + 2);
  printTree(a->dir, spaces + 2);
}

ArvoreRB *inserir(ArvoreRB *a, int v)
{
  if (a == NULL)
  {
    a = (ArvoreRB *)malloc(sizeof(ArvoreRB));
    a->info = v;
    a->cor = BLACK;
    a->esq = a->dir = NULL;
  }
  else if (v < a->info)
  {
    a->esq = inserir(a->esq, v);
    a->cor = RED;
  }
  else
  {
    a->dir = inserir(a->dir, v);
    a->cor = RED;
  }

  if (a->dir && a->esq && a->dir->cor == RED && a->esq->cor == BLACK)
    rot_esq(a);
  else if (a->esq && a->esq->esq && a->esq->cor == RED && a->esq->esq->cor == RED)
    rot_dir(a);
  else if (a->dir && a->esq && a->dir->cor == RED && a->esq->cor == RED)
    flip_cor(a);

  return a;
}

ArvoreRB *remover(ArvoreRB *a, int x)
{
  ArvoreRB *aux, *pai_aux;
  int filhos = 0, tmp;

  if (!a)
    return (NULL);

  if (a->info < x)
    a->dir = remover(a->dir, x);
  else if (a->info > x)
    a->esq = remover(a->esq, x);
  else
  {
    if (a->esq)
      filhos++;
    if (a->dir)
      filhos++;

    if (filhos == 0)
    {
      free(a);
      return (NULL);
    }
    else if (filhos == 1)
    {
      aux = a->esq ? a->esq : a->dir;
      free(a);
      return (aux);
    }
    else
    {
      aux = a->esq;
      pai_aux = a;
      while (aux->dir)
      {
        pai_aux = aux;
        aux = aux->dir;
      }
      tmp = a->info;
      a->info = aux->info;
      aux->info = tmp;
      pai_aux->dir = remover(aux, tmp);
      return (a);
    }
  }

  return (a);
}

int verifica_arv_vazia(ArvoreRB *a)
{
  return (a == NULL);
}

ArvoreRB *arv_libera(ArvoreRB *a)
{
  if (!verifica_arv_vazia(a))
  {
    arv_libera(a->esq);
    arv_libera(a->dir);
    free(a);
  }
  return NULL;
}

int arv_bin_check(ArvoreRB *a)
{
  return a == NULL
             ? 1
             : ((a->esq == NULL || a->info > a->esq->info) && (a->dir == NULL || a->info < a->dir->info) && arv_bin_check(a->esq) && arv_bin_check(a->dir));
}

ArvoreRB *rot_esq(ArvoreRB *no)
{
  ArvoreRB *tree = no->dir;
  no->dir = tree->esq;
  tree->esq = no;
  tree->cor = no->cor;
  no->cor = RED;
  return (tree);
}

ArvoreRB *rot_dir(ArvoreRB *no)
{
  ArvoreRB *tree = no->esq;
  no->esq = tree->dir;
  tree->dir = no;
  tree->cor = no->cor;
  no->cor = RED;
  return (tree);
}

void flip_cor(ArvoreRB *no)
{
  no->cor = RED;
  no->esq->cor = BLACK;
  no->dir->cor = BLACK;
}

int main()
{
  ArvoreRB *a;
  inserir(a, 5);
  inserir(a, 3);
  inserir(a, 9);
  inserir(a, 1);
  inserir(a, 4);
  inserir(a, 7);
  printTree(a);
  printTreeOrder(a);
  arv_libera(a);
}
