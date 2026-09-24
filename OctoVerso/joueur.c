#include "joueur.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

void initJoueur(Joueur* j) {
    j->reste = 0;
    j->mot[0] = '\0';
    j->chevalet = malloc(CAPACITE_MAIN * sizeof(char));
    if (j->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initJoueur\n");
        return;
    }
    memset(j->chevalet, ' ', CAPACITE_MAIN);
}

void libererJoueur(Joueur* j) {
    free(j->chevalet);
    j->chevalet = NULL;
}

int mainContientMot(const Joueur* j, const char* mot) {
    char copie[CAPACITE_MAIN];
    memcpy(copie, j->chevalet, CAPACITE_MAIN);

    for (int i = 0; mot[i] != '\0'; i++) {
        int trouve = 0;
        for (int k = 0; k < CAPACITE_MAIN; k++) {
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

// Copie n caractères en majuscules ; échoue si l'un d'eux n'est pas une lettre.
static int copierLettres(char* dst, const char* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char c = (char)toupper((unsigned char)src[i]);
        if (c < 'A' || c > 'Z') return 0;
        dst[i] = c;
    }
    dst[n] = '\0';
    return 1;
}

int jouerMotOuverture(Joueur* j, const char* saisie) {
    char mot[MOT4];
    if (strlen(saisie) != 4 || !copierLettres(mot, saisie, 4)) return 0;
    if (!mainContientMot(j, mot) || !verifMots(mot) || !verifMotDejaJouer(mot)) return 0;

    for (int i = 0; i < 4; i++) {
        retirerLettreMain(j, mot[i]);
    }
    memcpy(j->mot, mot, MOT4);
    return 1;
}

// Découpe "R (AB)CDE" ou "V CDE(AB)" en face, côté, lettres de la main et lettres du rail.
static int analyserCoup(const char* coup, char* face, int* aGauche, char* depuisMain, char* depuisRail) {
    while (*coup == ' ') coup++;
    *face = (char)toupper((unsigned char)*coup);
    if (*face != 'R' && *face != 'V') return 0;
    coup++;
    while (*coup == ' ') coup++;

    const char* ouvrante = strchr(coup, '(');
    const char* fermante = strchr(coup, ')');
    if (ouvrante == NULL || fermante == NULL || fermante < ouvrante) return 0;

    *aGauche = (ouvrante == coup);
    if (!*aGauche && fermante[1] != '\0') return 0;

    const char* debutRail = *aGauche ? fermante + 1 : coup;
    size_t longRail = *aGauche ? strlen(fermante + 1) : (size_t)(ouvrante - coup);
    size_t longMain = (size_t)(fermante - ouvrante - 1);
    if (longMain < 1 || longRail < 1 || longMain + longRail > TAILLE_RAIL) return 0;

    return copierLettres(depuisMain, ouvrante + 1, longMain)
        && copierLettres(depuisRail, debutRail, longRail);
}

int jouerCoup(Joueur* j, Rail* rail, const char* coup) {
    char face;
    int aGauche;
    char depuisMain[MOT_MAX], depuisRail[MOT_MAX];
    if (!analyserCoup(coup, &face, &aGauche, depuisMain, depuisRail)) return 0;

    size_t k = strlen(depuisMain), m = strlen(depuisRail);
    char f[TAILLE_RAIL + 1];
    lireFace(rail, face, f);
    const char* bord = aGauche ? f : f + TAILLE_RAIL - m;
    if (strncmp(bord, depuisRail, m) != 0) return 0;

    char mot[MOT_MAX];
    snprintf(mot, sizeof mot, "%s%s", aGauche ? depuisMain : depuisRail, aGauche ? depuisRail : depuisMain);
    if (!mainContientMot(j, depuisMain) || !verifMots(mot) || !verifMotDejaJouer(mot)) return 0;

    char expulsees[TAILLE_RAIL + 1];
    glisserSurRail(rail, face, aGauche, depuisMain, expulsees);
    for (size_t i = 0; i < k; i++) {
        retirerLettreMain(j, depuisMain[i]);
    }
    return (k + m == TAILLE_RAIL) ? 2 : 1;
}

int verifMots(const char* mot) {
    FILE* fic = fopen("ods4.txt", "r");
    if (fic == NULL) {
        printf("Erreur d'ouverture du fichier ods4.txt\n");
        return 0;
    }

    // Tampon de lecture distinct du mot à vérifier : on ne doit jamais écraser ce dernier.
    char motDico[32];
    int trouve = 0;
    while (fscanf(fic, "%31s", motDico) == 1) {
        if (strcmp(motDico, mot) == 0) {
            trouve = 1;
            break;
        }
    }
    fclose(fic);
    return trouve;
}

int verifMotDejaJouer(const char* mot) {
    static char motsJoues[256][MOT_MAX];
    static int nb = 0;

    for (int i = 0; i < nb; i++) {
        if (strcmp(motsJoues[i], mot) == 0) {
            return 0;
        }
    }
    if (nb < 256) {
        strncpy(motsJoues[nb], mot, MOT_MAX - 1);
        motsJoues[nb][MOT_MAX - 1] = '\0';
        nb++;
    }
    return 1;
}

void afficherMainJoueur(const Joueur* j) {
    char copie[CAPACITE_MAIN];
    memcpy(copie, j->chevalet, CAPACITE_MAIN);

    for (int i = 0; i < CAPACITE_MAIN - 1; i++) {
        for (int k = i + 1; k < CAPACITE_MAIN; k++) {
            if (copie[i] > copie[k]) {
                char temp = copie[i];
                copie[i] = copie[k];
                copie[k] = temp;
            }
        }
    }

    for (int i = 0; i < CAPACITE_MAIN; i++) {
        if (copie[i] != ' ') {
            printf("%c", copie[i]);
        }
    }
    printf(" (%d lettres)\n", j->reste);
}

void retirerLettreMain(Joueur* j, char lettre) {
    for (int i = 0; i < CAPACITE_MAIN; i++) {
        if (j->chevalet[i] == lettre) {
            j->chevalet[i] = ' ';
            j->reste--;
            return;
        }
    }
}

void ajouterLettreMain(Joueur* j, char lettre) {
    for (int i = 0; i < CAPACITE_MAIN; i++) {
        if (j->chevalet[i] == ' ') {
            j->chevalet[i] = lettre;
            j->reste++;
            return;
        }
    }
}

int estVideMain(const Joueur* j) {
    return j->reste == 0;
}
