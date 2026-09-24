#include "rail.h"
#include <stdio.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

void initRail(Rail* r, const char* gauche, const char* droite) {
    snprintf(r->recto, sizeof r->recto, "%s%s", gauche, droite);
}

void lireFace(const Rail* r, char face, char* sortie) {
    for (int i = 0; i < TAILLE_RAIL; i++) {
        sortie[i] = (face == 'V') ? r->recto[TAILLE_RAIL - 1 - i] : r->recto[i];
    }
    sortie[TAILLE_RAIL] = '\0';
}

void afficherRail(const Rail* r) {
    char verso[TAILLE_RAIL + 1];
    lireFace(r, 'V', verso);
    printf("R : %s\n", r->recto);
    printf("V : %s\n", verso);
}

void glisserSurRail(Rail* r, char face, int aGauche, const char* lettres, char* expulsees) {
    int k = (int)strlen(lettres);
    char f[TAILLE_RAIL + 1];
    char nouvelle[TAILLE_RAIL + 1];
    lireFace(r, face, f);

    if (aGauche) {
        memcpy(expulsees, f + TAILLE_RAIL - k, k);
        memcpy(nouvelle, lettres, k);
        memcpy(nouvelle + k, f, TAILLE_RAIL - k);
    }
    else {
        memcpy(expulsees, f, k);
        memcpy(nouvelle, f + k, TAILLE_RAIL - k);
        memcpy(nouvelle + TAILLE_RAIL - k, lettres, k);
    }
    expulsees[k] = '\0';
    nouvelle[TAILLE_RAIL] = '\0';

    // La face jouée devient `nouvelle` : si c'est le verso, le recto est son inverse.
    for (int i = 0; i < TAILLE_RAIL; i++) {
        r->recto[i] = (face == 'V') ? nouvelle[TAILLE_RAIL - 1 - i] : nouvelle[i];
    }
    r->recto[TAILLE_RAIL] = '\0';
}
