#include "joueur.h"
#include "paquet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

// Initialise un joueur : alloue un chevalet de taille FIXE (CHEVALETS cases), rempli d'espaces.
// Le chevalet ne change plus jamais de taille : ' ' marque une case vide, une lettre marque une case occupée.
void initJoueur(Joueur* j) {
    j->reste = 0;
    j->mot[0] = '\0';
    j->chevalet = malloc(CHEVALETS * sizeof(char));
    if (j->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initJoueur\n");
        return;
    }
    for (int i = 0; i < CHEVALETS; i++) {
        j->chevalet[i] = ' ';
    }
}

// Vérifie que toutes les lettres de `mot` sont disponibles dans le chevalet, sans consommer
// deux fois la même case (une lettre du chevalet ne peut servir qu'une fois par mot).
int mainContientMot(Joueur* j, const char* mot) {
    char copie[CHEVALETS];
    memcpy(copie, j->chevalet, CHEVALETS);

    for (int i = 0; mot[i] != '\0'; i++) {
        int trouve = 0;
        for (int k = 0; k < CHEVALETS; k++) {
            if (copie[k] == mot[i]) {
                copie[k] = ' ';
                trouve = 1;
                break;
            }
        }
        if (!trouve) return 0;
    }
    return 1;
}

// Propose un mot de 4 lettres : vérifie qu'il est bien dans la main et valide selon le
// dictionnaire, puis le pose sur le rail partagé (côté gauche) et retire les lettres jouées.
int proposerMots4Lettres(Joueur* j, Rail* rail) {
    char mot[MOT4];
    if (scanf(" %4s", mot) != 1) return 0;

    if (strlen(mot) != 4 || !mainContientMot(j, mot) || !verifMots(j, mot)) {
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        ajouterLettreRailGauche(rail, mot[i]);
        retirerLettreMain(j, mot[i]);
    }

    strncpy(j->mot, mot, MOT4);
    j->mot[MOT4 - 1] = '\0';
    return 1;
}

// Propose 2 lettres à ajouter sur le rail partagé, du côté choisi par le joueur.
// Format attendu : "<direction> <2 lettres>", direction = G (gauche) ou D (droite).
// Exemple : "D AB" ajoute A puis B du côté droit du rail.
int propose2Lettres(Joueur* j, Rail* rail) {
    char direction;
    char lettres[LETTRE2];
    if (scanf(" %c %2s", &direction, lettres) != 2) return 0;
    if (strlen(lettres) != 2 || !mainContientMot(j, lettres)) return 0;

    void (*ajouter)(Rail*, char) =
        (direction == 'D' || direction == 'd') ? ajouterLettreRailDroite : ajouterLettreRailGauche;

    ajouter(rail, lettres[0]);
    retirerLettreMain(j, lettres[0]);
    ajouter(rail, lettres[1]);
    retirerLettreMain(j, lettres[1]);
    return 1;
}

// Vérifie si le mot proposé figure dans le dictionnaire externe ods4.txt et n'a pas déjà
// été joué. Le tampon de lecture n'est PAS le tampon `mot` fourni par l'appelant : on ne
// doit jamais écraser le mot proposé pendant qu'on le compare au dictionnaire.
int verifMots(Joueur* j, char* mot) {
    FILE* fic = fopen("ods4.txt", "r");
    if (fic == NULL) {
        printf("Erreur d'ouverture du fichier ods4.txt\n");
        return 0;
    }

    char motDico[32];
    int trouve = 0;
    while (fscanf(fic, "%31s", motDico) != EOF) {
        if (strcmp(motDico, mot) == 0) {
            trouve = 1;
            break;
        }
    }
    fclose(fic);

    if (!trouve) return 0;
    return verifMotDejaJouer(j, mot);
}

// Vérifie si un mot a déjà été joué (par n'importe quel joueur) durant la partie.
int verifMotDejaJouer(Joueur* j, const char* mot) {
    (void)j; // gardé dans la signature pour cohérence d'API, non nécessaire à la vérification
    static char motsJoues[100][32];
    static int index = 0;

    for (int i = 0; i < index; i++) {
        if (strcmp(motsJoues[i], mot) == 0) {
            return 0;
        }
    }

    if (index < 100) {
        strncpy(motsJoues[index], mot, 31);
        motsJoues[index][31] = '\0';
        index++;
    }
    return 1;
}

// Affiche les lettres du chevalet du joueur, triées par ordre alphabétique.
void afficherMainJoueur(Joueur* j) {
    char copie[CHEVALETS];
    memcpy(copie, j->chevalet, CHEVALETS);

    for (int i = 0; i < CHEVALETS - 1; i++) {
        for (int k = i + 1; k < CHEVALETS; k++) {
            if (copie[i] > copie[k]) {
                char temp = copie[i];
                copie[i] = copie[k];
                copie[k] = temp;
            }
        }
    }

    for (int i = 0; i < CHEVALETS; i++) {
        if (copie[i] != ' ') {
            printf("%c", copie[i]);
        }
    }
    printf("\n");
}

// Retire une occurrence de `lettre` du chevalet (chevalet de taille fixe, pas de réallocation).
void retirerLettreMain(Joueur* j, char lettre) {
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] == lettre) {
            j->chevalet[i] = ' ';
            j->reste--;
            return;
        }
    }
}

// Ajoute une lettre dans la première case libre du chevalet (chevalet de taille fixe).
void ajouterLettreMain(Joueur* j, char lettre) {
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] == ' ') {
            j->chevalet[i] = lettre;
            j->reste++;
            return;
        }
    }
}

// Vérifie si le chevalet du joueur est vide.
int estVideMain(Joueur* j) {
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

// Propose un mot de 8 lettres (Octo Verso) sur le rail partagé (côté droit).
int proposerOctoVerso(Joueur* j, Rail* rail) {
    char mot[MOT8];
    if (scanf(" %8s", mot) != 1) return 0;
    if (strlen(mot) != 8 || !mainContientMot(j, mot) || !verifMots(j, mot)) return 0;

    for (int i = 0; i < 8; i++) {
        ajouterLettreRailDroite(rail, mot[i]);
        retirerLettreMain(j, mot[i]);
    }
    return 1;
}

// Variante Octo Verso : le joueur pose un mot de 8 lettres en piochant les lettres
// depuis la main de son adversaire plutôt que la sienne.
int proposerOctoAdversaire(Joueur* j, Joueur* adversaire, Rail* rail) {
    (void)j;
    char mot[MOT8];
    if (scanf(" %8s", mot) != 1) return 0;
    if (strlen(mot) != 8 || !mainContientMot(adversaire, mot) || !verifMots(adversaire, mot)) return 0;

    for (int i = 0; i < 8; i++) {
        ajouterLettreRailDroite(rail, mot[i]);
        retirerLettreMain(adversaire, mot[i]);
    }
    return 1;
}
