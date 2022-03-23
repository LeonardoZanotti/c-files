#include <stdio.h>
#include <stdlib.h>

typedef struct arvore
{
    char info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

Arvore *cria_arv_vazia(void)
{
    return NULL;
}

Arvore *arv_constroi(char c, Arvore *e, Arvore *d)
{
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    a->info = c;
    a->esq = e;
    a->dir = d;
    return a;
}

int verifica_arv_vazia(Arvore *a)
{
    return (a == NULL);
}

Arvore *arv_libera(Arvore *a)
{
    if (!verifica_arv_vazia(a))
    {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

int arv_pertence(Arvore *a, char c)
{
    return a != NULL && (a->info == c || arv_pertence(a->dir, c) || arv_pertence(a->esq, c));
}

void arv_imprime(Arvore *a)
{
    if (a == NULL)
        return;
    arv_imprime(a->esq);
    printf("%c \n", a->info);
    arv_imprime(a->dir);
}

int eh_espelho(Arvore *arv_a, Arvore *arv_b)
{
    return (arv_a == NULL && arv_b == NULL) || ((arv_a != NULL && arv_b != NULL) && (arv_a->info == arv_b->info && eh_espelho(arv_a->esq, arv_b->dir) && eh_espelho(arv_a->dir, arv_b->esq)));
}

Arvore *cria_espelho(Arvore *arv_a)
{
    return arv_a == NULL
               ? cria_arv_vazia()
               : arv_constroi(arv_a->info, cria_espelho(arv_a->dir), cria_espelho(arv_a->esq));
}

int main(int argc, char *argv[])
{
    Arvore *a = arv_constroi(
        'a',
        arv_constroi(
            'b',
            cria_arv_vazia(),
            arv_constroi(
                'd',
                cria_arv_vazia(),
                cria_arv_vazia())),
        arv_constroi(
            'c',
            arv_constroi(
                'e',
                cria_arv_vazia(),
                cria_arv_vazia()),
            arv_constroi(
                'f',
                cria_arv_vazia(),
                cria_arv_vazia())));

    Arvore *b = arv_constroi(
        'a',
        arv_constroi(
            'c',
            arv_constroi(
                'f',
                cria_arv_vazia(),
                cria_arv_vazia()),
            arv_constroi(
                'e',
                cria_arv_vazia(),
                cria_arv_vazia())),
        arv_constroi(
            'b',
            arv_constroi(
                'd',
                cria_arv_vazia(),
                cria_arv_vazia()),
            cria_arv_vazia()));

    Arvore *c = arv_constroi(
        'a',
        arv_constroi(
            'c',
            arv_constroi(
                'f',
                cria_arv_vazia(),
                cria_arv_vazia()),
            arv_constroi(
                'e',
                cria_arv_vazia(),
                cria_arv_vazia())),
        arv_constroi(
            'b',
            arv_constroi(
                'd',
                cria_arv_vazia(),
                cria_arv_vazia()),
            arv_constroi(
                'g',
                cria_arv_vazia(),
                cria_arv_vazia())));

    Arvore *a_esp = cria_espelho(a);

    // printf("%d %d", arv_pertence(a, 'f'), arv_pertence(a, 's'));

    arv_imprime(a);
    printf("\n");
    // arv_imprime(b);
    // printf("\n");
    // arv_imprime(c);
    // printf("\n");

    arv_imprime(a_esp);
    printf("\n");

    // printf("%d", eh_espelho(a, b));
    // printf("%d", eh_espelho(a, c));
    // printf("%d", eh_espelho(c, b));
    printf("%d", eh_espelho(a, a_esp));

    arv_libera(a);
    arv_libera(b);
    arv_libera(c);
    arv_libera(a_esp);
    return 0;
}
