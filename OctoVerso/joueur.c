#include "joueur.h"
#include "paquet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996 6031)

// Initialise un joueur : alloue et initialise son chevalet.
void initJoueur(Joueur* j) {
    j->reste = 0;
    j->chevalet = malloc(CHEVALETS * sizeof(char));
    if (j->chevalet == NULL) {
        printf("Erreur d'allocation memoire : initJoueur\n");
        return;
    }
    for (int i = 0; i < CHEVALETS; i++) {
        j->chevalet[i] = ' ';
    }
}

// Propose un mot de 4 lettres, vérifie sa validité et met à jour le chevalet et le rail.
int proposerMots4Lettres(Joueur* j) {
    char mot[MOT4];
    scanf("%s", mot);
    if (strlen(mot) == 4 && verifMots(j, mot) == 1) {
        for (int i = 0; i < MOT4; i++) {
            ajouterLettreRailGauche(j, mot[i]);
            retirerLettreMain(j, mot[i]);
        }
        return 1;
    }
    else {
        return 0;
    }
}

// Propose un mot de 2 lettres et met à jour le rail du joueur.
void propose2Lettres(Joueur* j) {
    char input[LETTRE2 + MOT4];
    scanf("%s", input);

    // Analyse et ajoute les lettres au rail en fonction de la direction.
    if (sscanf(input, "R (%*s) %2s", input) == 1 || sscanf(input, "V (%*s) %2s", input) == 1) {
        ajouterLettreRailDroite(&j->rail, input[0]);
        retirerLettreMain(j, input[0]);
        ajouterLettreRailDroite(&j->rail, input[1]);
        retirerLettreMain(j, input[1]);
    }
    else if (sscanf(input, "R %2s (%*s)", input) == 1 || sscanf(input, "V %2s (%*s)", input) == 1) {
        ajouterLettreRailGauche(&j->rail, input[0]);
        retirerLettreMain(j, input[0]);
        ajouterLettreRailGauche(&j->rail, input[1]);
        retirerLettreMain(j, input[1]);
    }
    if (sscanf(input, "R %8s", input) == 1 || sscanf(input, "V %8s", input) == 1) {
        proposerOctoVerso(j);
    }
}

// Vérifie si le mot proposé par le joueur est valide en le comparant avec un dictionnaire.
int verifMots(Joueur* j, char* mot) {
    FILE* fic = fopen("ods4.txt", "r");
    if (fic == NULL) {
        printf("Erreur d'ouverture du fichier ods4.txt\n");
        return 0;
    }

    char motJoueur[MOT4];
    int idx = 0;
    // Remplit le mot joueur à partir de son chevalet
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] != ' ') {
            motJoueur[idx++] = j->chevalet[i];
        }
    }
    motJoueur[idx] = '\0';

    // Vérifie si le mot existe dans le dictionnaire
    int trouve = 0;
    while (fscanf(fic, "%s", mot) != EOF) {
        if (strcmp(mot, motJoueur) == 0) {
            trouve = 1;
            return;
        }
    }

    fclose(fic);
    return trouve && verifMotDejaJouer(j) == 1;
}

// Vérifie si le mot a déjà été joué par le joueur.
int verifMotDejaJouer(Joueur* j) {
    static char motsJoues[100][MOT4];
    static int index = 0;

    // Vérifie si le mot a déjà été joué
    for (int i = 0; i < index; i++) {
        if (strcmp(motsJoues[i], j->mot) == 0) {
            return 0;
        }
    }

    // Ajoute le mot à la liste des mots joués
    strncpy(motsJoues[index], j->mot, MOT4);
    motsJoues[index][MOT4 - 1] = '\0';
    index++;
    return 1;
}

// Affiche les lettres restantes du chevalet du joueur.
void afficherMainJoueur(Joueur* j) {
    char copie[CHEVALETS];
    for (int i = 0; i < CHEVALETS; i++) {
        copie[i] = j->chevalet[i];
    }

    // Trier la copie par ordre alphabétique
    for (int i = 0; i < CHEVALETS - 1; i++) {
        for (int j = i + 1; j < CHEVALETS; j++) {
            if (copie[i] > copie[j]) {
                char temp = copie[i];
                copie[i] = copie[j];
                copie[j] = temp;
            }
        }
    }

    // Afficher les lettres triées 
    for (int i = 0; i < CHEVALETS; i++) {
        if (copie[i] != ' ') {
            printf("%c", copie[i]);
        }
    }
    printf("\n");
}

// Retire une lettre du chevalet du joueur.
void retirerLettreMain(Joueur* j, char lettre) {
    int trouve = 0;
    for (int i = 0; i < CHEVALETS; i++) {
        if (j->chevalet[i] == lettre) {
            j->chevalet[i] = ' ';
            trouve = 1;
        }
    }

    if (trouve) {
        j->reste--;
        char* temp = realloc(j->chevalet, j->reste * sizeof(char));
        if (temp == NULL && j->reste > 0) {
            printf("Erreur de reallocation de memoire : retirerLettreMain\n");
            return;
        }
        j->chevalet = temp;
    }
}

// Ajoute une lettre au chevalet du joueur.
void ajouterLettreMain(Joueur* j, char lettre) {
    int placeTrouvee = 0;
    for (int i = 0; i < j->reste; i++) {
        if (j->chevalet[i] == ' ') {
            j->chevalet[i] = lettre;
            placeTrouvee = 1;
            return;
        }
    }

    if (!placeTrouvee) {
        j->reste++;
        char* temp = realloc(j->chevalet, j->reste * sizeof(char));
        if (temp == NULL) {
            printf("Erreur de reallocation de memoire : ajouterLettreMain\n");
            return;
        }
        j->chevalet = temp;
        j->chevalet[j->reste - 1] = lettre;
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

// Propose un mot de 8 lettres pour l'octo verso et met à jour le chevalet et le rail.
void proposerOctoVerso(Joueur* j) {
    char mot[MOT8];
    if (strlen(mot) == 8 && verifMots(j, mot) == 1) {
        for (int i = 0; i < MOT8; i++) {
            ajouterLettreRailDroite(j, mot[i]);
            retirerLettreMain(j, mot[i]);
        }
    }
    return;
}

// Propose un mot de 8 lettres pour l'octo adversaire.
void proposerOctoAdversaire(Joueur* j, Joueur* adversaire) {
    char mot[MOT8];
    if (strlen(mot) == 8 && verifMots(j, mot) == 1) {
        for (int i = 0; i < MOT8; i++) {
            ajouterLettreRailDroite(&adversaire->rail, mot[i]);
            retirerLettreMain(j, mot[i]);
        }
    }
}