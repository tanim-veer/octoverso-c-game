#pragma once
#include "joueur.h"
#include "time.h"

enum {
    MAX_CARTES = 88,
};

typedef struct {
    int nombre;
    char lettre;
} Lettre;

typedef struct {
    char* chevalet;
    int reste;
} Paquet;

const static Lettre lettre[MAX_CARTES] = {
    {9, 'A'},
    {1, 'B'},
    {2, 'C'},
    {3, 'D'},
    {14,'E'},
    {1, 'F'},
    {1, 'G'},
    {5, 'H'},
    {7, 'I'},
    {1, 'J'},
    {5, 'L'},
    {3, 'M'},
    {6, 'N'},
    {5, 'O'},
    {7, 'P'},
    {6, 'Q'},
    {7, 'R'},
    {6, 'S'},
    {5, 'T'},
    {1, 'U'},
    {2, 'V'},
};

/**
 * @brief Initialise un paquet de lettres selon les fréquences de chaque lettre.
 * @param[out] p L'adresse du paquet à initialiser.
 */
void initPaquet(Paquet* p);

/**
 * @brief Mélange les lettres dans le paquet de manière aléatoire.
 * @param[in,out] p Le paquet à mélanger.
 */
void melangerPaquet(Paquet* p);

/**
 * @brief Distribue des lettres aux joueurs à partir du paquet.
 * @param[in,out] p Le paquet de lettres.
 * @param[in,out] j Le joueur à qui distribuer les lettres.
 */
void distribuerPaquet(Paquet* p, Joueur* j);

/**
 * @brief Détermine quel joueur a le mot le plus faible.
 * @param[in] j1 Le premier joueur.
 * @param[in] j2 Le second joueur.
 * @return L'indice du joueur ayant le mot le plus faible (0 ou 1).
 */
int determinerPremierJoueur(Joueur* j1, Joueur* j2);

/**
 * @brief Affiche l'état actuel du paquet.
 * @param[in] p Le paquet à afficher.
 */
void afficherPaquet(Paquet* p);

/**
 * @brief Affiche la situation actuelle du jeu (mains des joueurs et rails).
 * @param[in] j1 Le premier joueur.
 * @param[in] j2 Le second joueur.
 * @param[in] r Le rail à afficher.
 */
void afficherSituation(Joueur* j1, Joueur* j2, Rail* r);

/**
 * @brief Pioche une lettre du paquet.
 * @param[in,out] p Le paquet à partir duquel la lettre est piochée.
 * @return La lettre piochée.
 * @pre Le paquet ne doit pas être vide.
 */
char piocherLettreduPaquet(Paquet* p);

/**
 * @brief Retire une lettre du paquet.
 * @param[in,out] p Le paquet à modifier.
 * @param[in] lettre La lettre à retirer.
 */
void retirerLettrePaquet(Paquet* p, char lettre);

/**
 * @brief Vérifie si le paquet est vide.
 * @param[in] p Le paquet à vérifier.
 * @return 1 si le paquet est vide, 0 sinon.
 */
int estVidePaquet(Paquet* p);

/**
 * @brief Permet à un joueur d'échanger une lettre avec le paquet.
 * @param[in,out] j Le joueur qui échange une lettre.
 * @param[in,out] p Le paquet avec lequel le joueur échange.
 */
void echangeChevalet(Joueur* j, Paquet* p);
