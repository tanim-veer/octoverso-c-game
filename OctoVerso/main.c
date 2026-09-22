#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "joueur.h"
#include "rail.h"
#include "paquet.h"
#pragma warning (disable: 4996 6031)

// Complète la main du joueur jusqu'à CHEVALETS lettres en piochant dans le paquet.
static void completerMain(Joueur* j, Paquet* p) {
    while (j->reste < CHEVALETS && !estVidePaquet(p)) {
        char l = piocherLettreduPaquet(p);
        if (l == '\0') break;
        ajouterLettreMain(j, l);
    }
}

// Joue le tour du joueur `j` (son adversaire `adversaire` est nécessaire pour l'action Octo
// Adversaire). Renvoie 1 si un coup a réellement été joué, 0 si le joueur a passé ou si le
// coup tenté a été refusé.
static int jouerTour(Joueur* j, Joueur* adversaire, Rail* rail, Paquet* paquet, int numero) {
    printf("\n--- Tour du joueur %d ---\n", numero);
    printf("Main : ");
    afficherMainJoueur(j);
    printf("Rail R : ");
    afficherRailRecto(rail);
    printf("Rail V : ");
    afficherRailVerso(rail);
    printf("Action (4=mot de 4 lettres, 2=deux lettres, 8=octo verso, a=octo adversaire, e=echange, p=passer) : ");

    char action = 'p';
    if (scanf(" %c", &action) != 1) {
        action = 'p';
    }

    int joue = 0;
    switch (action) {
        case '4':
            printf("Mot (4 lettres) : ");
            joue = proposerMots4Lettres(j, rail);
            if (!joue) printf("Coup invalide, tour passe.\n");
            break;
        case '2':
            printf("Direction (G/D) et 2 lettres : ");
            joue = propose2Lettres(j, rail);
            if (!joue) printf("Coup invalide, tour passe.\n");
            break;
        case '8':
            printf("Mot (8 lettres) : ");
            joue = proposerOctoVerso(j, rail);
            if (!joue) printf("Coup invalide, tour passe.\n");
            break;
        case 'a':
            printf("Mot (8 lettres, pioche chez l'adversaire) : ");
            joue = proposerOctoAdversaire(j, adversaire, rail);
            if (!joue) printf("Coup invalide, tour passe.\n");
            break;
        case 'e':
            printf("Lettre a echanger : ");
            echangeChevalet(j, paquet);
            joue = 1; // l'echange n'est pas un "coup" a proprement parler, mais fait avancer la partie
            break;
        default:
            printf("Tour passe.\n");
            break;
    }

    completerMain(j, paquet);
    return joue;
}

int main() {
    srand((unsigned int)time(NULL));

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

    distribuerPaquet(paquet, j1);
    distribuerPaquet(paquet, j2);

    printf("=== Octo Verso ===\n");
    printf("1 : ");
    afficherMainJoueur(j1);
    printf("2 : ");
    afficherMainJoueur(j2);

    // Mot d'ouverture : chaque joueur propose un premier mot de 4 lettres.
    printf("Joueur 1, proposez votre premier mot de 4 lettres : ");
    while (proposerMots4Lettres(j1, rail) != 1) {
        printf("Mot invalide, reessayez : ");
    }
    printf("Joueur 2, proposez votre premier mot de 4 lettres : ");
    while (proposerMots4Lettres(j2, rail) != 1) {
        printf("Mot invalide, reessayez : ");
    }
    completerMain(j1, paquet);
    completerMain(j2, paquet);

    int joueurCourant = determinerPremierJoueur(j1, j2);
    afficherSituation(j1, j2, rail);

    // Partie : se termine quand le paquet est vide ET qu'un joueur n'a plus de lettres, ou
    // que les deux joueurs passent coup sur coup une fois le paquet vide (sinon, deux joueurs
    // qui ne feraient que passer garderaient la partie ouverte indéfiniment).
    int passesConsecutifs = 0;
    while (!estVidePaquet(paquet) || (!estVideMain(j1) && !estVideMain(j2))) {
        int aJoue;
        if (joueurCourant == 0) {
            aJoue = jouerTour(j1, j2, rail, paquet, 1);
        } else {
            aJoue = jouerTour(j2, j1, rail, paquet, 2);
        }
        passesConsecutifs = aJoue ? 0 : passesConsecutifs + 1;

        if (estVidePaquet(paquet) && passesConsecutifs >= 2) {
            break;
        }
        joueurCourant = 1 - joueurCourant;
    }

    printf("\n=== Fin de partie ===\n");
    printf("Lettres restantes - Joueur 1 : %d, Joueur 2 : %d\n", j1->reste, j2->reste);
    if (j1->reste < j2->reste) {
        printf("Le joueur 1 gagne !\n");
    } else if (j2->reste < j1->reste) {
        printf("Le joueur 2 gagne !\n");
    } else {
        printf("Egalite !\n");
    }

    // Libère l'allocation
    free(rail);
    free(paquet);
    free(j1);
    free(j2);
    return 0;
}
