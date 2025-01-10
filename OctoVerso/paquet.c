#include "paquet.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996 6031)

// Initialisation du paquet
void initPaquet(Paquet* p) {
    p->reste = 0;
    p->chevalet = malloc(MAX_CARTES * sizeof(char));

    if (p->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initPaquet\n");
        return;
    }

    // Remplir le chevalet avec les lettres
    for (int i = 0; i < sizeof(lettre) / sizeof(lettre[0]); i++) {
        for (int j = 0; j < lettre[i].nombre; j++) {
            p->chevalet[p->reste++] = lettre[i].lettre;
        }
    }
    melangerPaquet(p);  // Mélange les lettres
}

// Mélange aléatoire du paquet
void melangerPaquet(Paquet* p) {
    srand(time(NULL));  // Initialisation du random
    for (int i = 0; i < p->reste; i++) {
        int j = rand() % (i + 1);
        char tmp = p->chevalet[j];
        p->chevalet[j] = p->chevalet[i];
        p->chevalet[i] = tmp;
    }
}

// Distribue des lettres au joueur
void distribuerPaquet(Paquet* p, Joueur* j) {
    for (int i = 0; i < CHEVALETS; i++) {
        j->chevalet[i] = piocherLettreduPaquet(p);  // Pioche une lettre
    }
}

// Détermine quel joueur commence
int determinerPremierJoueur(Joueur* j1, Joueur* j2) {
    return strcmp(j1->mot, j2->mot) < 0 ? 0 : 1;
}


// Comparaison utilisée pour trier les caractères dans l'ordre alphabétique
int comparer2lettres(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// Affiche le paquet
void afficherPaquet(Paquet* p) {
    // Trier le paquet dans l'ordre alphabétique
    qsort(p->chevalet, p->reste, sizeof(char), comparer);

    // Afficher le paquet trié
    for (int i = 0; i < p->reste; i++) {
        printf("%c ", p->chevalet[i]);
    }
    printf("\n");
}

// Affiche la situation du jeu
void afficherSituation(Joueur* j1, Joueur* j2, Rail* r) {
    printf("1 : ");
    afficherMainJoueur(j1);
    printf("2 : ");
    afficherMainJoueur(j2);
    printf("R : ");
    afficherRailRecto(r);
    printf("V : ");
    afficherRailVerso(r);
}

// Pioche une lettre du paquet
char piocherLettreduPaquet(Paquet* p) {
    if (p->reste == 0) {
        return '\0';
    }
    return p->chevalet[p->reste--];
}

// Retire une lettre du paquet
void retirerLettrePaquet(Paquet* p, char lettre) {
    int trouve = 0;
    for (int i = 0; i < p->reste; i++) {
        if (p->chevalet[i] == lettre) {
            trouve = 1;
        }
        if (trouve && i < p->reste - 1) {
            p->chevalet[i] = p->chevalet[i + 1];
        }
    }

    if (trouve) {
        p->reste--;
        char* temp = realloc(p->chevalet, p->reste * sizeof(char));
        if (temp == NULL && p->reste > 0) {
            printf("Erreur de réallocation mémoire : retirerLettrePaquet\n");
            return;
        }
        p->chevalet = temp;
    }
}

// Vérifie si le paquet est vide
int estVidePaquet(Paquet* p) {
    return p->reste == 0;
}

// Échange une lettre entre le joueur et le paquet
void echangeChevalet(Joueur* j, Paquet* p) {
    char lettre;
    scanf("%c", &lettre);
    retirerLettreMain(j, lettre);  // Retirer de la main du joueur
    piocherLettreduPaquet(p, j);  // Pioche une nouvelle lettre
}