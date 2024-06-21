#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac)
{
    if (racine == NULL)
    {
        *nb_esp = 0;
        *nb_carac = 0;
        return;
    }

    int nb1_esp = 0, nb2_esp = 0;
    int nb1_car = 0, nb2_car = 0;

    analyse_arbre(racine->gauche, &nb1_esp, &nb1_car);
    analyse_arbre(racine->droit, &nb2_esp, &nb2_car);

    *nb_esp = nb1_esp + nb2_esp;
    *nb_carac = nb1_car + nb2_car;

    if (racine->gauche == NULL && racine->droit == NULL)
        *nb_esp += 1;
    else
        *nb_carac += 1;
}

/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */

///////////////////////////////////////////////////////////////

/* Convert an integer to string */
char *int_to_string(char *value)
{
    return strdup(value);
}

/* Convert a subtree to a string */
char *subtree_to_string(arbre subroot)
{
    if (subroot == NULL)
    {
        return strdup(""); // Return an empty string for an empty subtree
    }

    char *left_str = subtree_to_string(subroot->gauche);
    char *right_str = subtree_to_string(subroot->droit);

    char *subroot_str = int_to_string(subroot->valeur);

    // Allocate memory for the final string
    size_t len = strlen(left_str) + strlen(right_str) + strlen(subroot_str) + 3; // 3 for comma and parentheses
    char *result = (char *)malloc(len);

    // Build the final string
    snprintf(result, len, "(%s,%s,%s)", left_str, subroot_str, right_str);

    // Free temporary strings
    free(left_str);
    free(right_str);
    free(subroot_str);

    return result;
}

////////////////////////////////////////////////////////


int rechercher_espece(arbre racine, char *espece, liste_t *seq)
{
    if (racine == NULL)
    {
        return 1;
    }

    if (strcmp(racine->valeur, espece) == 0) {
        // Clear the list and return 0 when the species is found
        liberer_liste(seq);
        return 0;
    }
        if (racine->gauche != NULL)
        {
            // Push the left subtree to the list
            char *left_subtree_str = subtree_to_string(racine->gauche);
            ajouter_tete(seq, left_subtree_str);
            free(left_subtree_str); // Free the allocated string when done
        }

        if (racine->droit != NULL)
        {
            // Push the right subtree to the list
            char *right_subtree_str = subtree_to_string(racine->droit);
            ajouter_tete(seq, right_subtree_str);
            free(right_subtree_str); // Free the allocated string when done
        }

    int found_in_left = rechercher_espece(racine->gauche, espece, seq);
    if (found_in_left == 0)
    {
        if (racine->droit != NULL)
        {
            // Push the right subtree to the list
           // char *right_subtree_str = subtree_to_string(racine->droit);
            //ajouter_tete(seq,  racine->valeur);

        
        return 0;
        }
    }

    int found_in_right = rechercher_espece(racine->droit, espece, seq);
    if (found_in_right == 0)
    {
        if (racine->gauche != NULL)
        {
            // Push the left subtree to the list
            //char *left_subtree_str = subtree_to_string(racine->gauche);
            ajouter_tete(seq, racine->valeur);
        }
        return 0;
    }

    return 1;
}






/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{
    // Check if the tree is empty
    if (*a == NULL)
    {
        // Create a new node for the species
        *a = (arbre)malloc(sizeof(struct noeud_s));
        if (*a == NULL)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            return 1; // Memory allocation error
        }

        // Initialize the new node
        (*a)->valeur = strdup(espece);
        (*a)->gauche = NULL;
        (*a)->droit = NULL;

        // Add the characteristics to the list
        cellule_t *current = seq;
        while (current->suivant != NULL)
        {
            current = current->suivant;
        }

        // Assuming that characteristics are stored in espece
        current->suivant = (cellule_t *)malloc(sizeof(cellule_t));
        if (current->suivant == NULL)
        {
            fprintf(stderr, "Erreur d'allocation de mémoire\n");
            free(*a);
            *a = NULL;
            return 1; // Memory allocation error
        }
        current->suivant->val = strdup(espece);
        current->suivant->suivant = NULL;

        return 0; // Species added successfully
    }

    // If the tree is not empty, traverse the tree to find the correct position
    int cmp = strcmp(espece, (*a)->valeur);
    if (cmp < 0)
    {
        return ajouter_espece(&((*a)->gauche), espece, seq);
    }
    else if (cmp > 0)
    {
        return ajouter_espece(&((*a)->droit), espece, seq);
    }
    else
    {
        // Species already exists in the tree
        return 1;
    }
}


/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
    printf("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
    printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
    return 0;
}
