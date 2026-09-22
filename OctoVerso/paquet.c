#include "paquet.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable: 4996 6031)

// Initialise le paquet avec le bon nombre d'exemplaires de chaque lettre, puis le mélange.
void initPaquet(Paquet* p) {
    p->reste = 0;
    p->chevalet = malloc(MAX_CARTES * sizeof(char));

    if (p->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initPaquet\n");
        return;
    }

    // Remplir le paquet avec les lettres (NB_LETTRES_DISTINCTES entrées seulement : le
    // tableau `lettre` ne contient pas MAX_CARTES entrées, mais un exemplaire par lettre
    // distincte avec sa fréquence).
    for (int i = 0; i < NB_LETTRES_DISTINCTES; i++) {
        for (int j = 0; j < lettre[i].nombre; j++) {
            p->chevalet[p->reste++] = lettre[i].lettre;
        }
    }
    melangerPaquet(p);
}

// Mélange aléatoirement le paquet (Fisher-Yates). Le générateur aléatoire est initialisé
// une seule fois par le programme (dans main), pas ici.
void melangerPaquet(Paquet* p) {
    for (int i = p->reste - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char tmp = p->chevalet[j];
        p->chevalet[j] = p->chevalet[i];
        p->chevalet[i] = tmp;
    }
}

// Distribue jusqu'à CHEVALETS lettres au joueur, en s'arrêtant si le paquet se vide avant.
void distribuerPaquet(Paquet* p, Joueur* j) {
    for (int i = 0; i < CHEVALETS; i++) {
        char l = piocherLettreduPaquet(p);
        if (l == '\0') break;
        ajouterLettreMain(j, l);
    }
}

// Détermine quel joueur commence : celui dont le mot d'ouverture est alphabétiquement le plus petit.
int determinerPremierJoueur(Joueur* j1, Joueur* j2) {
    return strcmp(j1->mot, j2->mot) < 0 ? 0 : 1;
}

// Comparaison utilisée pour trier les caractères dans l'ordre alphabétique.
int comparer2lettres(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// Affiche le paquet trié par ordre alphabétique (utile pour le débogage / suivi de partie).
void afficherPaquet(Paquet* p) {
    qsort(p->chevalet, p->reste, sizeof(char), comparer);
    for (int i = 0; i < p->reste; i++) {
        printf("%c ", p->chevalet[i]);
    }
    printf("\n");
}

// Affiche l'état complet de la partie : main des deux joueurs et rail partagé.
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

// Pioche et retire la dernière lettre du paquet ('\0' si le paquet est vide).
char piocherLettreduPaquet(Paquet* p) {
    if (p->reste == 0) {
        return '\0';
    }
    p->reste--;
    return p->chevalet[p->reste];
}

// Retire une lettre précise du paquet, en décalant les lettres suivantes pour combler le trou.
void retirerLettrePaquet(Paquet* p, char lettre) {
    for (int i = 0; i < p->reste; i++) {
        if (p->chevalet[i] == lettre) {
            for (int k = i; k < p->reste - 1; k++) {
                p->chevalet[k] = p->chevalet[k + 1];
            }
            p->reste--;
            return;
        }
    }
}

// Vérifie si le paquet est vide.
int estVidePaquet(Paquet* p) {
    return p->reste == 0;
}

// Échange une lettre de la main du joueur contre une nouvelle lettre piochée dans le paquet.
void echangeChevalet(Joueur* j, Paquet* p) {
    char lettre;
    if (scanf(" %c", &lettre) != 1) return;

    int possede = 0;
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] == lettre) {
            possede = 1;
            break;
        }
    }
    if (!possede) return;

    retirerLettreMain(j, lettre);
    char nouvelle = piocherLettreduPaquet(p);
    if (nouvelle != '\0') {
        ajouterLettreMain(j, nouvelle);
    }
}
