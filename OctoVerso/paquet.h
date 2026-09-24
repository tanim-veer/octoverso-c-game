#pragma once
#include "joueur.h"

enum {
    NB_LETTRES_DISTINCTES = 21,
    MAX_CARTES = 88,       // somme exacte des fréquences ci-dessous
};

typedef struct {
    int nombre;
    char lettre;
} Lettre;

typedef struct {
    char* chevalet;
    int reste;
} Paquet;

static const Lettre lettre[NB_LETTRES_DISTINCTES] = {
    {9, 'A'},
    {1, 'B'},
    {2, 'C'},
    {3, 'D'},
    {14,'E'},
    {1, 'F'},
    {1, 'G'},
    {1, 'H'},
    {7, 'I'},
    {1, 'J'},
    {5, 'L'},
    {3, 'M'},
    {6, 'N'},
    {5, 'O'},
    {2, 'P'},
    {1, 'Q'},
    {6, 'R'},
    {7, 'S'},
    {6, 'T'},
    {5, 'U'},
    {2, 'V'},
};

/**
 * @brief Initialise le paquet selon les fréquences de chaque lettre, puis le mélange.
 * @param[out] p Le paquet à initialiser.
 */
void initPaquet(Paquet* p);

/**
 * @brief Libère la mémoire du paquet.
 */
void libererPaquet(Paquet* p);

/**
 * @brief Mélange les lettres du paquet de manière aléatoire.
 */
void melangerPaquet(Paquet* p);

/**
 * @brief Distribue CHEVALETS lettres au joueur (moins si le paquet se vide).
 */
void distribuerPaquet(Paquet* p, Joueur* j);

/**
 * @brief Détermine quel joueur commence : celui dont le mot d'ouverture est le plus petit alphabétiquement.
 * @return 0 pour le premier joueur, 1 pour le second.
 */
int determinerPremierJoueur(const Joueur* j1, const Joueur* j2);

/**
 * @brief Pioche une lettre du paquet.
 * @return La lettre piochée, ou '\0' si le paquet est vide.
 */
char piocherLettreduPaquet(Paquet* p);

/**
 * @brief Vérifie si le paquet est vide.
 * @return 1 si le paquet est vide, 0 sinon.
 */
int estVidePaquet(const Paquet* p);
