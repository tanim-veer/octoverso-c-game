#include "rail.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996 6031)

// Agrandit la taille du rail si nécessaire en doublant sa capacité.
void augmenterTailleRail(char** rail, int* size, int* capacite) {
    if (*size >= *capacite) {
        *capacite *= 2;
        char* tmp = realloc(*rail, *capacite * sizeof(char));
        if (tmp == NULL) {
            printf("Erreur de reallocation memoire : augmenterTailleRail\n");
            return;
        }
        *rail = tmp;
    }
}

// Initialise les rails (recto et verso) du joueur.
void initRail(Rail* r) {
    r->recto = malloc(TAILLE_RAIL * sizeof(char));
    r->verso = malloc(TAILLE_RAIL * sizeof(char));
    r->size_recto = 1;
    r->size_verso = 1;
    r->capacite_recto = TAILLE_RAIL;
    r->capacite_verso = TAILLE_RAIL;

    if (r->recto == NULL || r->verso == NULL) {
        printf("Erreur d'allocation memoire: initRail\n");
        return;
    }

    // Remplir les rails avec des espaces vides au départ
    for (int i = 0; i < TAILLE_RAIL; i++) {
        r->recto[i] = ' ';
        r->verso[i] = ' ';
    }
}

// Comparaison pour trier les lettres dans l'ordre alphabétique
int comparer(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// Affiche les lettres du rail recto après les avoir triées.
void afficherRailRecto(Rail* r) {
    qsort(r->recto, r->size_recto, sizeof(char), comparer);
    for (int i = 0; i < r->size_recto; i++) {
        printf("%c ", r->recto[i]);
    }
    printf("\n");
}

// Affiche les lettres du rail verso après les avoir triées.
void afficherRailVerso(Rail* r) {
    qsort(r->verso, r->size_verso, sizeof(char), comparer);
    for (int i = 0; i < r->size_verso; i++) {
        printf("%c ", r->verso[i]);
    }
    printf("\n");
}

// Ajoute une lettre sur le rail gauche (recto ou verso).
void ajouterLettreRailGauche(Rail* r, char lettre) {
    int i;
    // Essaye d'ajouter la lettre dans le recto
    for (i = r->size_recto - 1; i >= 0; i--) {
        if (r->recto[i] == ' ') {
            r->recto[i] = lettre;
            return;
        }
    }

    // Si le recto est plein, essaye d'ajouter dans le verso
    for (i = r->size_verso - 1; i >= 0; i--) {
        if (r->verso[i] == ' ') {
            r->verso[i] = lettre;
            return;
        }
    }

    // Si les deux rails sont pleins, agrandit le rail approprié et ajoute la lettre
    if (r->size_recto >= r->size_verso) {
        augmenterTailleRail(&r->recto, &r->size_recto, &r->capacite_recto);
        for (i = r->size_recto; i > 0; i--) {
            r->recto[i] = r->recto[i - 1];
        }
        r->recto[0] = lettre;
        r->size_recto++;
    }
    else {
        augmenterTailleRail(&r->verso, &r->size_verso, &r->capacite_verso);
        for (i = r->size_verso; i > 0; i--) {
            r->verso[i] = r->verso[i - 1];
        }
        r->verso[0] = lettre;
        r->size_verso++;
    }
}

// Ajoute une lettre sur le rail droit (recto ou verso).
void ajouterLettreRailDroite(Rail* r, char lettre) {
    int i;
    // Essaye d'ajouter la lettre dans le recto
    for (i = 0; i < r->size_recto; i++) {
        if (r->recto[i] == ' ') {
            r->recto[i] = lettre;
            return;
        }
    }

    // Essaye d'ajouter la lettre dans le verso
    for (i = 0; i < r->size_verso; i++) {
        if (r->verso[i] == ' ') {
            r->verso[i] = lettre;
            return;
        }
    }

    // Si les deux rails sont pleins, agrandit le rail approprié et ajoute la lettre
    if (r->size_recto < r->size_verso) {
        augmenterTailleRail(&r->recto, &r->size_recto, &r->capacite_recto);
        r->recto[r->size_recto] = lettre;
        r->size_recto++;
    }
    else {
        augmenterTailleRail(&r->verso, &r->size_verso, &r->capacite_verso);
        r->verso[r->size_verso] = lettre;
        r->size_verso++;
    }
}

// Retire une lettre du rail gauche (recto ou verso).
void retirerLettreRailGauche(Rail* r, char lettre) {
    int i;
    // Cherche la lettre dans le recto et dans le verso
    for (i = 0; i < r->size_recto; i++) {
        if (r->recto[i] == lettre) {
            r->recto[i] = ' ';
            break;
        }
    }

    for (i = 0; i < r->size_verso; i++) {
        if (r->verso[i] == lettre) {
            r->verso[i] = ' ';
            break;
        }
    }

    // Réduire la taille si plus de la moitié des espaces sont vides
    int vide_recto = 0, vide_verso = 0;
    for (i = 0; i < r->size_recto; i++) {
        if (r->recto[i] == ' ') vide_recto++;
    }
    for (i = 0; i < r->size_verso; i++) {
        if (r->verso[i] == ' ') vide_verso++;
    }

    if (vide_recto > (r->size_recto / 2)) {
        char* tmp = realloc(r->recto, (r->size_recto - 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Erreur de reallocation memoire pour le recto : retirerLettreRailGauche\n");
            return;
        }
        r->recto = tmp;
        r->size_recto--;
    }

    if (vide_verso > (r->size_verso / 2)) {
        char* tmp = realloc(r->verso, (r->size_verso - 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Erreur de reallocation memoire pour le verso: retirerLettreRailGauche\n");
            return;
        }
        r->verso = tmp;
        r->size_verso--;
    }
}

// Retire une lettre du rail droit (recto ou verso).
void retirerLettreRailDroite(Rail* r, char lettre) {
    int i;
    // Cherche la lettre sur le recto et le verso, de droite à gauche
    for (i = r->size_recto - 1; i >= 0; i--) {
        if (r->recto[i] == lettre) {
            r->recto[i] = ' ';
            break;
        }
    }

    for (i = r->size_verso - 1; i >= 0; i--) {
        if (r->verso[i] == lettre) {
            r->verso[i] = ' ';
            break;
        }
    }

    // Réduit la taille des rails si plus de la moitié des espaces sont vides
    int vide_recto = 0, vide_verso = 0;
    for (i = 0; i < r->size_recto; i++) {
        if (r->recto[i] == ' ') vide_recto++;
    }
    for (i = 0; i < r->size_verso; i++) {
        if (r->verso[i] == ' ') vide_verso++;
    }

    if (vide_recto > (r->size_recto / 2)) {
        char* tmp = realloc(r->recto, (r->size_recto - 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Erreur de reallocation memoire pour le recto : retirerLettreRailDroite\n");
            return;
        }
        r->recto = tmp;
        r->size_recto--;
    }

    if (vide_verso > (r->size_verso / 2)) {
        char* tmp = realloc(r->verso, (r->size_verso - 1) * sizeof(char));
        if (tmp == NULL) {
            printf("Erreur de reallocation memoire pour le verso : retirerLettreRailDroite\n");
            return;
        }
        r->verso = tmp;
        r->size_verso--;
    }
}

// Vide les rails en réinitialisant leur contenu
void viderRail(Rail* r) {
    for (int i = 0; i < TAILLE_RAIL; i++) {
        r->recto[i] = ' ';
        r->verso[i] = ' ';
    }
    r->size_recto = 0;
    r->size_verso = 0;
}

// Vérifie si les deux rails sont pleins
int estPlein(Rail* r) {
    for (int i = 0; i < TAILLE_RAIL; i++) {
        if (r->recto[i] == ' ' || r->verso[i] == ' ') {
            return 0; // Si un espace est vide, les rails ne sont pas pleins
        }
    }
    return 1; // Les rails sont pleins
}