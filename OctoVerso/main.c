#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "joueur.h"
#include "rail.h"
#include "paquet.h"
#pragma warning (disable: 4996 6031)

int main() {
    srand(time(NULL));
    Rail* rail = (Rail*)malloc(sizeof(Rail));
    Paquet* paquet = (Paquet*)malloc(sizeof(Paquet));
    Joueur* j1 = (Joueur*)malloc(sizeof(Joueur));
    Joueur* j2 = (Joueur*)malloc(sizeof(Joueur));

    // Vérification de l'allocation
    if (rail == NULL || paquet == NULL || j1 == NULL || j2 == NULL) {
        printf("Erreur d'allocation de memoire\n");
        return 1;
    }

    // Initialisation des éléments du jeu
    initRail(rail);
    initPaquet(paquet);
    initJoueur(j1);
    initJoueur(j2);

    melangerPaquet(paquet);
    distribuerPaquet(paquet, j1);
    distribuerPaquet(paquet, j2);

    // Premier Tour
    printf("1 : ");
    afficherMainJoueur(j1);
    printf("2 : ");
    afficherMainJoueur(j2);

    do {
        printf("1> ");
    } while (proposerMots4Lettres(j1) != 1);

    do {
        printf("2> ");
    } while (proposerMots4Lettres(j2) != 1);

    int premierJoueur = determinerPremierJoueur(j1, j2);
    afficherSituation(j1, j2, rail);

    // Partie
    while (etatPartie != 1) {
        if (premierJoueur == 0) {
            printf("1> ");
            premierJoueur = 1;

        }
        else if (premierJoueur == 1) {
            printf("2> ");
            premierJoueur = 0;
        }
    }

    // Free l'allocation
    free(rail);
    free(paquet);
    free(j1);
    free(j2);
}