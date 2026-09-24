#include "paquet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

void initPaquet(Paquet* p) {
    p->reste = 0;
    p->chevalet = malloc(MAX_CARTES * sizeof(char));
    if (p->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initPaquet\n");
        return;
    }

    for (int i = 0; i < NB_LETTRES_DISTINCTES; i++) {
        for (int j = 0; j < lettre[i].nombre; j++) {
            p->chevalet[p->reste++] = lettre[i].lettre;
        }
    }
    melangerPaquet(p);
}

void libererPaquet(Paquet* p) {
    free(p->chevalet);
    p->chevalet = NULL;
}

// Mélange de Fisher-Yates. Le générateur aléatoire est initialisé une seule fois, dans main.
void melangerPaquet(Paquet* p) {
    for (int i = p->reste - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char tmp = p->chevalet[j];
        p->chevalet[j] = p->chevalet[i];
        p->chevalet[i] = tmp;
    }
}

void distribuerPaquet(Paquet* p, Joueur* j) {
    for (int i = 0; i < CHEVALETS; i++) {
        char l = piocherLettreduPaquet(p);
        if (l == '\0') break;
        ajouterLettreMain(j, l);
    }
}

int determinerPremierJoueur(const Joueur* j1, const Joueur* j2) {
    return strcmp(j1->mot, j2->mot) < 0 ? 0 : 1;
}

char piocherLettreduPaquet(Paquet* p) {
    if (p->reste == 0) {
        return '\0';
    }
    p->reste--;
    return p->chevalet[p->reste];
}

int estVidePaquet(const Paquet* p) {
    return p->reste == 0;
}
