#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */

void init_liste_vide(liste_t *L)
{
    /* a completer */

    L->tete = NULL;
}

void liberer_liste(liste_t *L)
{
    /* a completer */

    while (L->tete != NULL)
    {
        cellule_t *temp = L->tete;
        L->tete = L->tete->suivant;
        free(temp);
    }
}

int ajouter_tete(liste_t *L, string c)
{
    /* a completer */

    cellule_t *cell = malloc(sizeof(cellule_t));

    // Allocate memory for the string and copy the content
    cell->val = malloc(strlen(c) + 1);
    strcpy(cell->val, c);

    cell->suivant = L->tete;
    L->tete = cell;

    return 0;
}

