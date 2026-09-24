#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "joueur.h"
#include "rail.h"
#include "paquet.h"
#pragma warning (disable: 4996 6031)

// Lit une ligne sans le retour à la ligne ni les espaces finaux. Renvoie 0 si l'entrée est fermée.
static int lireLigne(char* buf, int taille) {
    if (fgets(buf, taille, stdin) == NULL) return 0;
    size_t n = strlen(buf);
    while (n > 0 && (buf[n - 1] == '\n' || buf[n - 1] == '\r' || buf[n - 1] == ' ')) {
        buf[--n] = '\0';
    }
    return 1;
}

// Renvoie -1 si l'entrée est fermée, 0 si le joueur passe, 1 pour un coup joué, 2 pour un Octo Verso.
static int jouerTour(Joueur* j, Rail* rail, Paquet* paquet, int numero) {
    printf("\n--- Tour du joueur %d ---\n", numero);
    afficherRail(rail);
    printf("Main : ");
    afficherMainJoueur(j);
    printf("Coup (ex : R (AB)CDE ou V CDE(AB)), - pour passer : ");

    char saisie[64];
    while (lireLigne(saisie, sizeof saisie)) {
        if (strcmp(saisie, "-") == 0) {
            char l = piocherLettreduPaquet(paquet);
            if (l != '\0') {
                ajouterLettreMain(j, l);
                printf("Le joueur %d passe et pioche une lettre.\n", numero);
            }
            else {
                printf("Le joueur %d passe (paquet vide).\n", numero);
            }
            return 0;
        }

        int avant = j->reste;
        int r = jouerCoup(j, rail, saisie);
        if (r > 0) {
            printf("Coup accepte : %d lettre(s) posee(s), autant de tuiles sortent du rail.\n", avant - j->reste);
            if (r == 2) printf("OCTO VERSO ! Le joueur %d rejoue.\n", numero);
            return r;
        }
        printf("Coup invalide, reessayez (- pour passer) : ");
    }
    return -1;
}

int main(void) {
    srand((unsigned int)time(NULL));
    // Sans buffer : les invites s'affichent avant la saisie même si la sortie est redirigée.
    setvbuf(stdout, NULL, _IONBF, 0);

    Paquet paquet;
    Joueur j1, j2;
    Joueur* joueurs[2] = { &j1, &j2 };
    initPaquet(&paquet);
    initJoueur(&j1);
    initJoueur(&j2);
    if (paquet.chevalet == NULL || j1.chevalet == NULL || j2.chevalet == NULL) {
        return 1;
    }

    distribuerPaquet(&paquet, &j1);
    distribuerPaquet(&paquet, &j2);

    printf("=== Octo Verso ===\n");
    char saisie[64];
    int entreeFermee = 0;
    for (int i = 0; i < 2 && !entreeFermee; i++) {
        printf("\n%d : ", i + 1);
        afficherMainJoueur(joueurs[i]);
        printf("Joueur %d, votre mot d'ouverture (4 lettres) : ", i + 1);
        for (;;) {
            if (!lireLigne(saisie, sizeof saisie)) {
                entreeFermee = 1;
                break;
            }
            if (jouerMotOuverture(joueurs[i], saisie)) break;
            printf("Mot invalide, reessayez : ");
        }
    }

    int gagnant = -1;
    if (!entreeFermee) {
        // Le mot le plus petit alphabétiquement est placé à gauche du rail, et son joueur commence.
        int courant = determinerPremierJoueur(&j1, &j2);
        Rail rail;
        initRail(&rail, joueurs[courant]->mot, joueurs[1 - courant]->mot);
        printf("\nLe rail est forme : le joueur %d commence.\n", courant + 1);

        // Deux passes de suite une fois le paquet vide terminent la partie : sans cette règle,
        // deux joueurs bloqués passeraient indéfiniment.
        int passes = 0;
        for (;;) {
            int r = jouerTour(joueurs[courant], &rail, &paquet, courant + 1);
            if (r < 0) break;
            if (estVideMain(joueurs[courant])) {
                gagnant = courant;
                break;
            }
            passes = (r == 0) ? passes + 1 : 0;
            if (passes >= 2 && estVidePaquet(&paquet)) break;
            if (r != 2) courant = 1 - courant;
        }

        printf("\n=== Fin de partie ===\n");
        printf("Lettres restantes - Joueur 1 : %d, Joueur 2 : %d\n", j1.reste, j2.reste);
        if (gagnant < 0 && j1.reste != j2.reste) {
            gagnant = (j1.reste < j2.reste) ? 0 : 1;
        }
        if (gagnant >= 0) printf("Le joueur %d gagne !\n", gagnant + 1);
        else printf("Egalite !\n");
    }

    libererJoueur(&j1);
    libererJoueur(&j2);
    libererPaquet(&paquet);
    return entreeFermee ? 1 : 0;
}
